#include "Booster.h"

Booster::Booster()
{
}


Booster::Booster(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_staticBody;

	l_bodyDef.position.Set(def->pos.x, def->pos.y);
	l_bodyDef.angle = def->fOrientation * Deg2Rad;

	m_body = world->CreateBody(&l_bodyDef);

	l_shape.SetAsBox(def->size.x * 0.5f, def->size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = 1.0f;
	l_fixtureDef.friction = 0.0f;
	l_fixtureDef.restitution = 0.0f;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;

	m_body->CreateFixture(&l_fixtureDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);

	SetSpeedModifier(def->boost);
}

void Booster::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(Booster).name(), this));
}

void Booster::SetSpeedModifier(b2Vec2 modifier)
{
	m_fModifier = modifier;
}

float Booster::getAngle()
{
	return m_body->GetAngle() * Rad2Deg;
}

b2Vec2 Booster::GetSpeedModifier()
{
	return m_fModifier;
}

void Booster::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

Booster::~Booster()
{
	delete m_body->GetUserData();
}
