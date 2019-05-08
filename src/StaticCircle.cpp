#include "StaticCircle.h"

StaticCircle::StaticCircle()
{
}

StaticCircle::StaticCircle(b2World * world, Definition * def)
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

	l_fixtureDef.filter.categoryBits = STATIC_OBJECT;
	l_fixtureDef.filter.maskBits = DYNAMIC_OBJECT | BALL;

	m_body->CreateFixture(&l_fixtureDef);

	shape.setPosition(def->pos);
	shape.setRadius(def->fRadius);
	shape.setOrigin(def->fRadius, def->fRadius);
	shape.setTexture(def->texture);
}

void StaticCircle::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(StaticCircle).name(), this));
}

void StaticCircle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

StaticCircle::~StaticCircle()
{
	delete m_body->GetUserData();
}
