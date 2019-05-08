#pragma once

/*!
\file RotatingBlock.h
\class RotatingBlock
\brief Rotating block class

Contains data about a rotating block and creates it. Inherits from KinematicShape.
*/

#include "Shape.h"
#include "Definition.h"

class RotatingBlock : public KinematicShape
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;
	//! angVelocity initial constant angular velocity
	float angVelocity;
public:
	//! Default constructor
	RotatingBlock();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	RotatingBlock(b2World *world, Definition *def);
	//! Updates entity's position
	void update();
	// !Sets user data used with collisions
	void SetUserData();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~RotatingBlock();
};