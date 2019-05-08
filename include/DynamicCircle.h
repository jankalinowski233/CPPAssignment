#pragma once

/*!
\file DynamicCircle.h
\class DynamicCircle
\brief Creates movable circle

Holds general data about movable circle and creates it. Dynamic circles can be used as e.g. movable
wood logs. Inherits from DynamicShape.
*/

#include "Shape.h"
#include "Definition.h"

class DynamicCircle : public DynamicShape
{
private:
	//! SFML's circle shape
	sf::CircleShape shape;
	
	//! Initial linear damping
	float originalLinDamp;
	//! Initial angular damping
	float originalAngDamp;
public:
	//! Default constructor
	DynamicCircle();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	DynamicCircle(b2World *world, Definition *def);
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
	//! Changes angular damping
	/*!
	\param damp new angular damping
	*/
	void SetAngularDamping(float damp);
	//! Changes linear damping
	/*!
	\param damp new linear damping
	*/
	void SetLinearDamping(float damp);
	//! Returns current linear damping
	/*!
	\returns current linear damping
	*/
	float GetLinearDamping();
	//! Returns current angular damping
	/*!
	\returns current angular damping
	*/
	float GetAngularDamping();

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

	//! Sets user data used with collision
	void SetUserData();
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
	~DynamicCircle();

	//! Boolean to control whether entity has entered the ramp
	bool circleOnRamp = false;
};