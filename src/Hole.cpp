#include "Hole.h"

Hole::Hole()
{
}

Hole::Hole(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2CircleShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_staticBody;
	l_bodyDef.position.Set(def->pos.x, def->pos.y);

	m_body = world->CreateBody(&l_bodyDef);

	l_shape.m_radius = def->fRadius;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;

	l_fixtureDef.filter.categoryBits = STATIC_OBJECT;
	l_fixtureDef.filter.maskBits = BALL;

	m_body->CreateFixture(&l_fixtureDef);

	hole.setPosition(def->pos);
	hole.setRadius(def->fRadius * 2.f);
	hole.setOrigin(def->fRadius * 2.f, def->fRadius * 2.f);
	hole.setFillColor(sf::Color::Black);
}

void Hole::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(Hole).name(), this));
}

void Hole::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(hole);
}

Hole::~Hole()
{
	delete m_body->GetUserData();
}
