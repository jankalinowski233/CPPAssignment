#include "DynamicCircle.h"

#include <iostream>

DynamicCircle::DynamicCircle()
{
}

DynamicCircle::DynamicCircle(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2CircleShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(def->pos.x, def->pos.y);
	l_bodyDef.angle = def->fOrientation * Deg2Rad;

	m_body = world->CreateBody(&l_bodyDef);

	l_shape.m_radius = def->fRadius;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_fixtureDef.filter.categoryBits = DYNAMIC_OBJECT; //category
	l_fixtureDef.filter.maskBits = STATIC_OBJECT | DYNAMIC_OBJECT | BALL;

	originalAngDamp = def->fAngularDamping;
	originalLinDamp = def->fLinearDamping;

	m_body->SetAngularDamping(originalAngDamp);
	m_body->SetLinearDamping(originalLinDamp);

	m_body->CreateFixture(&l_fixtureDef);

	shape.setPosition(def->pos);
	shape.setRadius(def->fRadius);
	shape.setOrigin(def->fRadius, def->fRadius);
	shape.setRotation(def->fOrientation);
	shape.setTexture(def->texture);
}

void DynamicCircle::update()
{
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle()* Rad2Deg;
	shape.setRotation(angle);
}

void DynamicCircle::Boost(b2Vec2 boost)
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(boost.x, boost.y), true);
}

void DynamicCircle::ApplyForce(b2Vec2 force)
{
	m_body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void DynamicCircle::SetAngularDamping(float damp)
{
	m_body->SetAngularDamping(damp);
}

void DynamicCircle::SetLinearDamping(float damp)
{
	m_body->SetLinearDamping(damp);
}

float DynamicCircle::GetLinearDamping()
{
	return m_body->GetLinearDamping();
}

float DynamicCircle::GetAngularDamping()
{
	return m_body->GetAngularDamping();
}

float DynamicCircle::getOriginalLinDamp()
{
	return originalLinDamp;
}

float DynamicCircle::getOriginalAngDamp()
{
	return originalAngDamp;
}

void DynamicCircle::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(DynamicCircle).name(), this));
}

bool DynamicCircle::OnRamp()
{
	onRamp = circleOnRamp;
	return onRamp;
}

void DynamicCircle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);

	sf::RectangleShape line(sf::Vector2f(shape.getRadius(), 0.01f));
	line.setPosition(shape.getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(shape.getRotation());
	target.draw(line);
}

DynamicCircle::~DynamicCircle()
{
	delete m_body->GetUserData();
}
