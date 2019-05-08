#include "SlidingDoor.h"

#include <iostream>

SlidingDoor::SlidingDoor()
{
}

SlidingDoor::SlidingDoor(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_kinematicBody;

	l_bodyDef.position.Set(def->pos.x, def->pos.y);
	l_bodyDef.angle = def->fOrientation * Deg2Rad;

	m_body = world->CreateBody(&l_bodyDef);

	l_shape.SetAsBox(def->size.x * 0.5f, def->size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_fixtureDef.filter.categoryBits = DYNAMIC_OBJECT;
	l_fixtureDef.filter.maskBits = BALL | STATIC_OBJECT | DYNAMIC_OBJECT;

	m_body->CreateFixture(&l_fixtureDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);

	setID(def->id);
	state = CLOSED;
	m_fMotionTime = def->speedModifier;
}

void SlidingDoor::setID(int id)
{
	m_doorID = id;
}

int SlidingDoor::getID()
{
	return m_doorID;
}

void SlidingDoor::update(float timestep)
{
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * Rad2Deg;
	shape.setRotation(angle);

	//linear interpolation of movement
	if (state == OPENING)
	{
		m_fTime += timestep;
		float t = m_fTime / m_fMotionTime;
		float dist;

		if (t < 1.0f)
		{
			dist = t * -0.5f;
		}
		else
		{
			dist = -0.5f;
		}
		open(dist);

		if (m_fTime > m_fMotionTime)
		{
			state = OPEN;
			m_body->SetLinearVelocity(b2Vec2(0, 0));
		}
	}
}

void SlidingDoor::open(float force)
{
	b2Vec2 imp;
	imp = b2Vec2(0.f, 1.f);

	float theta = (m_body->GetAngle() - (90.f * Deg2Rad));
	float cosf = cos(theta);
	float sinf = sin(theta);

	b2Vec2 temp;
	temp.x = imp.x * cosf - imp.y * sinf;
	temp.y = imp.x * sinf + imp.y * cosf;

	m_body->SetLinearVelocity(b2Vec2(temp.x * force, temp.y * force));
}

void SlidingDoor::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(SlidingDoor).name(), this));
}

void SlidingDoor::changeDoorState()
{
	if (state == CLOSED)
	{
		state = OPENING;
	}
}

void SlidingDoor::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

SlidingDoor::~SlidingDoor()
{
	delete m_body->GetUserData();
}
