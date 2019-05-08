#pragma once

/*!
\file Booster.h
\class Booster
\brief Creates booster

Holds general data about the booster and provides its functionality. Booster applies
a single impulse to dynamic entities. Inherits from Sensor.
*/

#include "Sensor.h"
#include "Definition.h"

class Booster : public Sensor
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;
public:
	//! Default constructor
	Booster();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	Booster(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Sets boost strength
	/*!
	\param modifier new strength
	*/
	void SetSpeedModifier(b2Vec2 modifier);
	//! Returns angle
	/*!
	\returns angle
	*/
	float getAngle();
	//! Returns boost strength
	/*!
	\returns speed modifier
	*/
	b2Vec2 GetSpeedModifier();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~Booster();
};