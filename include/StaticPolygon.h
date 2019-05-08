#pragma once

/*!
\file StaticPolygon.h
\class StaticPolygon
\brief Creates static polygon shapes

Holds general data about the static polygon shape and provides its functionality. Static polygons can be used to create
e.g. walls or another various obstacles. Inherits from StaticShape.
*/

#include "Shape.h"
#include "Definition.h"

class StaticPolygon : public StaticShape
{
private:
	//! SFML's convex shape
	sf::ConvexShape shape;
public:
	//! Default constructor
	StaticPolygon();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	StaticPolygon(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~StaticPolygon();
};
