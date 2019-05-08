#pragma once

/*!
\file StaticBlock.h
\class StaticBlock
\brief Creates static blocks

Holds general data about the static block and provides its functionality. Static blocks can be used to create
e.g. walls. Inherits from StaticShape.
*/

#include "Shape.h"
#include "Definition.h"

class StaticBlock : public StaticShape
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;
public:
	//! Default constructor
	StaticBlock();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	StaticBlock(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~StaticBlock();
};