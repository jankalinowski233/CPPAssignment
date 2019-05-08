#pragma once

/*!
\file Ramp.h
\class Ramp
\brief Creates ramp

Holds general data about the ramp and provides its functionality. Ramp applies
constant force to dynamic entities. Inherits from Sensor.
*/

#include "Sensor.h"
#include "Definition.h"

class Ramp : public Sensor
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;

public:
	//! Default constructor
	Ramp();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	Ramp(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Sets force strength
	/*!
	\param modifier new strength
	*/
	void SetSpeedModifier(b2Vec2 modifier);
	//! Returns force strength
	/*!
	\returns speed modifier
	*/
	b2Vec2 GetSpeedModifier();
	//! Returns angle
	/*!
	\returns angle
	*/
	float getAngle();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~Ramp();
};