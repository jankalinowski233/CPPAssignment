#include "Door.h"

Door::Door()
{
}

Door::Door(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_dynamicBody;

	l_bodyDef.position.Set(def->pos.x, def->pos.y);
	l_bodyDef.angle = def->fOrientation * Deg2Rad;

	//create an anchor in the middle of the entity
#pragma region Anchor

	b2BodyDef l_anchDef;
	b2CircleShape l_anchShape;
	b2FixtureDef l_anchFix;
	l_anchDef.type = b2_staticBody;
	l_anchDef.position.Set(def->pos.x, def->pos.y);
	l_anchShape.m_radius = 0.001f;
	l_anchFix.shape = &l_anchShape;
	anchor = world->CreateBody(&l_anchDef);
	anchor->CreateFixture(&l_anchFix);

#pragma endregion

	m_body = world->CreateBody(&l_bodyDef);

	l_shape.SetAsBox(def->size.x * 0.5f, def->size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_fixtureDef.filter.categoryBits = DYNAMIC_OBJECT;
	l_fixtureDef.filter.maskBits = BALL | STATIC_OBJECT | DYNAMIC_OBJECT;

	//create joint
	b2RevoluteJointDef revJointDef;
	revJointDef.bodyA = m_body;
	revJointDef.bodyB = anchor;
	revJointDef.collideConnected = false;

	setAngularDamping(def->fAngularDamping);

	m_body->CreateFixture(&l_fixtureDef);

	world->CreateJoint(&revJointDef);

	shape.setSize(def->size);
	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setOrigin(def->size * 0.5f);
	shape.setRotation(def->fOrientation);
}

void Door::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(Door).name(), this));
	anchor->SetUserData((void*) new std::pair<std::string, void*>("null", this));
}

void Door::update()
{
	b2Vec2 pos = m_body->GetPosition();
	shape.setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* Rad2Deg;
	shape.setRotation(angle);
}

void Door::setAngularDamping(float damp)
{
	m_body->SetAngularDamping(damp);
}

void Door::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

Door::~Door()
{
	delete m_body->GetUserData();
	delete anchor->GetUserData();
}
