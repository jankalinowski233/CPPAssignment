#pragma once

/*!
\file DynamicBlock.h
\class DynamicBlock
\brief Creates movable block

Holds general data about movable block and creates it. Dynamic blocks may be used as e.g. movable chests or 
blocks of wood. Inherits from DynamicShape.
*/

#include "Shape.h"
#include "Definition.h"

class DynamicBlock : public DynamicShape
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;

	//! Initial linear damping
	float originalLinDamp;
	//! Initial angular damping
	float originalAngDamp;
public:
	//! Default constructor
	DynamicBlock();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	DynamicBlock(b2World *world, Definition *def);
	//! Updates entity's position
	void update();
	//! Boosts entity
	/*!
	\param boost strength and direction of the boost
	*/
	void Boost(b2Vec2 boost);
	//! Applies constant force
	/*!
	\param force strength and direction of force
	*/
	void ApplyForce(b2Vec2 force);
	//! Sets user data used with collision
	void SetUserData();
	//! Changes angular damping
	/*!
	\param damping new angular damping
	*/
	void SetAngularDamping(float damping);
	//! Changes linear damping
	/*!
	\param damping new linear damping
	*/
	void SetLinearDamping(float damping);
	//! Returns current angular damping
	/*!
	\returns current angular damping
	*/
	float GetAngularDamping();
	//! Returns current linear damping
	/*!
	\returns current linear damping
	*/
	float GetLinearDamping();

	//! Returns initial linear damping
	/*!
	\returns original linear damping
	*/
	float getOriginalLinDamp();
	//! Returns initial angular damping
	/*!
	\returns original angular damping
	*/
	float getOriginalAngDamp();

	//! Controls if entity started colliding with ramp
	/*!
	\returns true if colliding with ramp
	*/
	bool OnRamp();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~DynamicBlock();

	//! Boolean to control whether entity has entered the ramp
	bool blockOnRamp = false;
};