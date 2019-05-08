#include "StaticBlock.h"

StaticBlock::StaticBlock()
{
}

StaticBlock::StaticBlock(b2World *world, Definition *def)
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

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_fixtureDef.filter.categoryBits = STATIC_OBJECT;
	l_fixtureDef.filter.maskBits = DYNAMIC_OBJECT | BALL;

	m_body->CreateFixture(&l_fixtureDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture); 
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);
}

void StaticBlock::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(StaticBlock).name(), this));
}

void StaticBlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

StaticBlock::~StaticBlock()
{
	delete m_body->GetUserData();
}
