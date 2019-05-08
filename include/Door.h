#pragma once

/*!
\file Door.h
\class Door
\brief Creates hittable door on an anchor

Holds general data about hittable door and creates it. Doors can be created to constraint access to 
certain areas in the game. Inherits from DynamicShape.
*/

#include "Shape.h"
#include "Definition.h"

class Door : public DynamicShape
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;

	//! Box2D's body of an anchor
	b2Body *anchor;
	//! Box2D's revolute joint
	b2RevoluteJoint *joint;
public:
	//! Custom constructor
	Door();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	Door(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Updates entity's position
	void update();
	//! Sets angular damping
	/*!
	\param damp new angular damping
	*/
	void setAngularDamping(float damp);
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~Door();
};