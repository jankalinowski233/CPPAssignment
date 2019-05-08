#include "DoorOpener.h"
#include "Game.h"

#include <iostream>

DoorOpener::DoorOpener()
{
}

DoorOpener::DoorOpener(b2World * world, Definition * def)
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
	
	setID(def->id);
}

void DoorOpener::openDoor(int id)
{
	Game *game = game->getInstance();

	//loop through every door
	for (SlidingDoor *door : game->m_slidingDoors)
	{
		//if id have matched
		if (id == door->getID())
		{
			door->changeDoorState();
		}
	}
}

void DoorOpener::setID(int id)
{
	m_id = id;
}

int DoorOpener::getID()
{
	return m_id;
}

void DoorOpener::changeTexture(sf::Texture * tex)
{
	if (m_texChanged == false)
	{
		shape.setTexture(tex);
		m_texChanged = true;
	}
		
}

void DoorOpener::SetUserData()
{
	m_body->SetUserData((void*) new std::pair<std::string, void*>(typeid(DoorOpener).name(), this));
}

void DoorOpener::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

DoorOpener::~DoorOpener()
{
	delete m_body->GetUserData();
}
