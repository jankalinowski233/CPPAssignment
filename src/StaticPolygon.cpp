#include "StaticPolygon.h"

StaticPolygon::StaticPolygon()
{
}

StaticPolygon::StaticPolygon(b2World * world, Definition * def)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_staticBody;

	//create a triangle
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(def->pos.x, def->pos.y));
	shape.setPoint(1, sf::Vector2f(def->pos.x, def->pos.y - def->polygonExtents));
	shape.setPoint(2, sf::Vector2f(def->pos.x + def->polygonExtents, def->pos.y));

	b2Vec2 vertices[3];
	vertices[0].Set(shape.getPoint(0).x, shape.getPoint(0).y);
	vertices[1].Set(shape.getPoint(1).x, shape.getPoint(1).y);
	vertices[2].Set(shape.getPoint(2).x, shape.getPoint(2).y);

	l_shape.Set(vertices, 3);
	l_shape.m_radius = 0.0f;

	l_bodyDef.position.Set(def->pos.x, def->pos.y);
	l_bodyDef.angle = def->fOrientation * Deg2Rad;

	m_body = world->CreateBody(&l_bodyDef);

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_fixtureDef.filter.categoryBits = STATIC_OBJECT;
	l_fixtureDef.filter.maskBits = DYNAMIC_OBJECT | BALL;

	m_body->CreateFixture(&l_fixtureDef);

	shape.setTexture(def->texture);
	shape.setPosition(def->pos);
	shape.setRotation(def->fOrientation);
}

void StaticPolygon::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(StaticPolygon).name(), this));
}

void StaticPolygon::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

StaticPolygon::~StaticPolygon()
{
	delete m_body->GetUserData();
}
