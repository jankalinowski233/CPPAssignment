#include "Ball.h"
#include <iostream>
Ball::Ball()
{
}

Ball::Ball(b2World * world, Definition * def)
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

	l_fixtureDef.filter.categoryBits = BALL; //category
	l_fixtureDef.filter.maskBits = STATIC_OBJECT | DYNAMIC_OBJECT | HOLE;

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

void Ball::ApplyRotation(sf::Vector2f rotation)
{
	//Get current rotation
	rotation = sf::Vector2f(rotation.x - m_body->GetPosition().x, rotation.y - m_body->GetPosition().y);
	//target rotation
	b2Vec2 target = b2Vec2(rotation.x, rotation.y);
	//rotate
	angle = atan2f(-target.x, target.y);
	angle += 90.f * Deg2Rad;
	m_body->SetTransform(m_body->GetPosition(), angle);
}

float Ball::getAngle()
{
	return m_body->GetAngle() * Rad2Deg;
}

b2Vec2 Ball::getLinearVelocity()
{
	return m_body->GetLinearVelocity();
}

sf::Vector2f Ball::getPosition()
{
	return shape.getPosition();
}

void Ball::ApplyLinearImpulse(float force)
{
	//set angle
	b2Vec2 imp;
	imp = b2Vec2(0.f, 1.f);

	float theta = (getAngle() - 90.f) * Deg2Rad;
	float cosf = cos(theta);
	float sinf = sin(theta);

	//apply impulse
	b2Vec2 temp;
	temp.x = imp.x * cosf - imp.y * sinf;
	temp.y = imp.x * sinf + imp.y * cosf;

	m_body->ApplyLinearImpulseToCenter(b2Vec2(temp.x * force, temp.y * force), true);
}

void Ball::update()
{
	//update position
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);

	//update rotation
	float angle = m_body->GetAngle()* Rad2Deg;
	shape.setRotation(angle);
}

void Ball::Boost(b2Vec2 boost)
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(boost.x, boost.y), true);
}

void Ball::ApplyForce(b2Vec2 force)
{
	m_body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void Ball::SetAngularDamping(float damp)
{
	m_body->SetAngularDamping(damp);
}

void Ball::SetLinearDamping(float damp)
{
	m_body->SetLinearDamping(damp);
}

float Ball::GetLinearDamping()
{
	return m_body->GetLinearDamping();
}

float Ball::GetAngularDamping()
{
	return m_body->GetAngularDamping();
}

float Ball::getOriginalLinDamp()
{
	return originalLinDamp;
}

float Ball::getOriginalAngDamp()
{
	return originalAngDamp;
}

void Ball::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(Ball).name(), this));
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);

	//create a custom line from the centre to the edge of the ball
	sf::RectangleShape line(sf::Vector2f(shape.getRadius(), 0.01f));
	line.setPosition(shape.getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(shape.getRotation());
	line.setFillColor(sf::Color::Red);
	target.draw(line);
}

Ball::~Ball()
{
	//clean memory
	delete m_body->GetUserData();
}
