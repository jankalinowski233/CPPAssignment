#pragma once

/*!
\file StaticCircle.h
\class StaticCircle
\brief Creates static circles

Holds general data about the static circles and provides its functionality. Static blocks can be used to create
various obstacles. Inherits from StaticShape.
*/

#include "Shape.h"
#include "Definition.h"

class StaticCircle : public StaticShape
{
private:
	//! SFML's circle shape
	sf::CircleShape shape;
public:
	//! Default constructor
	StaticCircle();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	StaticCircle(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~StaticCircle();
};