#pragma once

/*!
\file ShapeFactory.h
\class ShapeFactory
\brief Creates all entities in game's world

Creates an entity depending on the type read from LevelLoader class.
Makes use of factory pattern.
*/

#include "Game.h"
#include "Definition.h"
#include "RotatingBlock.h"
#include "Door.h"
#include "DoorOpener.h"
#include "Star.h"

class ShapeFactory
{
private:
	//! Pointer to the Box2D's world
	b2World * world;

public:
	//! Creates static entities
	/*!
	\param def pointer to Definition class
	\returns new static entity
	*/
	StaticShape* makeStaticShape(Definition *def)
	{
		StaticShape * shape = nullptr;
		if (def->getType() == "StaticBlock")
		{
			shape = new StaticBlock(world, def);
		}
		if (def->getType() == "StaticPolygon")
		{
			shape = new StaticPolygon(world, def);
		}
		if (def->getType() == "StaticCircle") 
		{
			shape = new StaticCircle(world, def);
		}
		if (def->getType() == "Booster")
		{
			shape = new Booster(world, def);
		}
		if (def->getType() == "SpeedChanger")
		{
			shape = new SpeedChanger(world, def);
		}
		if (def->getType() == "Ramp")
		{
			shape = new Ramp(world, def);
		}
		if (def->getType() == "Hole")
		{
			shape = new Hole(world, def);
		}
		if (def->getType() == "DoorOpener")
		{
			shape = new DoorOpener(world, def);
		}
	
		shape->SetUserData();
		return shape;
	}

	//! Creates kinematic entities
	/*!
	\param def pointer to Definition class
	\returns new kinematic entity
	*/
	KinematicShape* makeKinematicShape(Definition *def)
	{
		KinematicShape *shape = nullptr;
		if (def->getType() == "RotatingBlock")
		{
			shape = new RotatingBlock(world, def);
		}

		shape->SetUserData();
		return shape;
	}

	//! Creates dynamic entities
	/*!
	\param def pointer to Definition class
	\returns new dynamic entity
	*/
	DynamicShape* makeDynamicShape(Definition *def)
	{
		DynamicShape *shape = nullptr;
		if (def->getType() == "DynamicBlock")
		{
			shape = new DynamicBlock(world, def);
		}
		if (def->getType() == "DynamicCircle")
		{
			shape = new DynamicCircle(world, def);
		}
		if (def->getType() == "Door")
		{
			shape = new Door(world, def);
		}

		shape->SetUserData();
		return shape;
	}

	//! Creates sliding door
	/*!
	\param def pointer to Definition class
	\returns new sliding door
	*/
	SlidingDoor *makeDoor(Definition *def)
	{
		SlidingDoor *door = nullptr;
		if (def->getType() == "SlidingDoor")
		{
			door = new SlidingDoor(world, def);
		}
		door->SetUserData();
		return door;
	}

	//! Creates stars
	/*!
	\param def pointer to Definition class
	\returns new star
	*/
	Star *makeStar(Definition *def)
	{
		Star *s = nullptr;
		if (def->getType() == "Star")
		{
			s = new Star(world, def);
		}
		s->SetUserData();
		return s;
	}

	//! Creates ball
	/*!
	\param def pointer to Definition class
	\returns ball
	*/
	Ball* makeBall(Definition *def)
	{
		Ball* ball;
		ball = new Ball(world, def);
		ball->SetUserData();
		return ball;
	}

	//! Sets world
	/*!
	\param newWorld world relegation
	*/
	void setWorld(b2World *newWorld)
	{
		world = newWorld;
	};
};