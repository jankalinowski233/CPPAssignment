#include "DynamicBlock.h"

DynamicBlock::DynamicBlock()
{
}

DynamicBlock::DynamicBlock(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_dynamicBody;

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

	originalAngDamp = def->fAngularDamping;
	originalLinDamp = def->fLinearDamping;

	m_body->SetAngularDamping(originalAngDamp);
	m_body->SetLinearDamping(originalLinDamp);

	m_body->CreateFixture(&l_fixtureDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);
}

void DynamicBlock::update()
{
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* Rad2Deg;
	shape.setRotation(angle);
}

void DynamicBlock::Boost(b2Vec2 boost)
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(boost.x, boost.y), true);
}

void DynamicBlock::ApplyForce(b2Vec2 force)
{
	m_body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void DynamicBlock::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(DynamicBlock).name(), this));
}

void DynamicBlock::SetAngularDamping(float damping)
{
	m_body->SetAngularDamping(damping);
}

void DynamicBlock::SetLinearDamping(float damping)
{
	m_body->SetLinearDamping(damping);
}

float DynamicBlock::GetAngularDamping()
{
	return m_body->GetAngularDamping();
}

float DynamicBlock::GetLinearDamping()
{
	return m_body->GetLinearDamping();
}

float DynamicBlock::getOriginalLinDamp()
{
	return originalLinDamp;
}

float DynamicBlock::getOriginalAngDamp()
{
	return originalAngDamp;
}

bool DynamicBlock::OnRamp()
{
	onRamp = blockOnRamp;
	return onRamp;
}

void DynamicBlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

DynamicBlock::~DynamicBlock()
{
	delete m_body->GetUserData();
}
