#include "RotatingBlock.h"

RotatingBlock::RotatingBlock()
{
}

RotatingBlock::RotatingBlock(b2World * world, Definition * def)
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
	l_fixtureDef.filter.maskBits = BALL | DYNAMIC_OBJECT;

	m_body->SetAngularVelocity(def->speedModifier);

	m_body->CreateFixture(&l_fixtureDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);
}

void RotatingBlock::update()
{
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * Rad2Deg;
	shape.setRotation(angle);
}

void RotatingBlock::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(RotatingBlock).name(), this));
}

void RotatingBlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

RotatingBlock::~RotatingBlock()
{
	delete m_body->GetUserData();
}
