#pragma once

/*!
\file Ball.h
\class Ball
\brief Creates ball (player)

Holds general data about the ball and provides its functionality. Ball is also a player. Inherits from DynamicShape.
*/

#include "Shape.h"
#include "Definition.h"
#include "Booster.h"
#include "Ramp.h"
#include "SpeedChanger.h"

class Ball : public DynamicShape
{
private:
	//! SFML's circle shape
	sf::CircleShape shape;

	//! initial linear damping of the ball
	float originalLinDamp;
	//! initial angular damping of the ball
	float originalAngDamp;

	//! initial orientation of the ball
	float angle = 0.f;
public:
	//! Default constructor
	Ball();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	Ball(b2World *world, Definition *def);
	
	//! Returns linear velocity
	/*!
	\returns body's linear velocity
	*/
	b2Vec2 getLinearVelocity();
	//! Returns angle
	/*!
	\returns angle
	*/
	float getAngle();
	//! Returns position
	/*!
	\returns body's position
	*/
	sf::Vector2f getPosition();

	//! Rotates ball towards mouse position
	/*!
	\param rotation mouse position on the screen
	*/
	void ApplyRotation(sf::Vector2f rotation);
	//! Applies impulse to the ball
	/*!
	\param force amount of force to apply
	*/
	void ApplyLinearImpulse(float force);
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

	//! Sets user data used with collisions
	void SetUserData();
	//! Updates entity's position
	void update();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//! Destructor
	~Ball();

	//! Boolean to control whether ball has entered the ramp
	bool isOnRamp = false;
	//! Boolean to control whether player has scored
	bool scored = false;
};