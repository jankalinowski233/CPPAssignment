#pragma once

/*!
\file Hole.h
\class Hole
\brief Creates goal

Holds general data about the goal point and provides its functionality. Once player reaches the goal
the game ends. Inherits from Sensor.
*/

#include "Sensor.h"
#include "Definition.h"

class Hole : public Sensor
{
private:
	//! SFML's circle shape
	sf::CircleShape hole;

public:
	//! Default constructor
	Hole();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	Hole(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~Hole();
};