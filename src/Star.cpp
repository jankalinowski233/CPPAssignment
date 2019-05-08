#include "Star.h"
#include "TextureManager.h"

Star::Star()
{
}

Star::Star(b2World * world, Definition * def)
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

	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;

	l_fixtureDef.filter.categoryBits = DYNAMIC_OBJECT;
	l_fixtureDef.filter.maskBits = BALL;

	m_body->SetAngularVelocity(def->speedModifier);

	m_body->CreateFixture(&l_fixtureDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);
}

void Star::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(Star).name(), this));
}

void Star::update()
{
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * Rad2Deg;
	shape.setRotation(angle);

	//should the star be deleted?
	if (deletionFlag == true)
	{
		b2World *tempWorld = m_body->GetWorld();
		tempWorld->DestroyBody(m_body);
		deletionFlag = false;
	}
}

void Star::createUIStar(sf::Vector2f pos)
{
	TextureManager *texManager = texManager->getInstance();

	shape.setSize(sf::Vector2f(50.f, 50.f));
	shape.setRotation(0.f);
	shape.setPosition(pos);
	shape.setOrigin(sf::Vector2f(25.f, 25.f));
	shape.setTexture(texManager->getTexture("star"));
}

void Star::DeleteStar()
{
	deletionFlag = true;
}

void Star::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

Star::~Star()
{
	tex = nullptr;
	m_body = nullptr;
}
