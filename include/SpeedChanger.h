#pragma once

/*!
\file SpeedChanger.h
\class SpeedChanger
\brief Creates an entity changing linear and/or angular damping

Holds general data about the speed changer (e.g. ice or sand) and provides its functionality.
Changes dynamic entities angular and linear damping as soon as collision occurs. Inherits from Sensor.
*/

#include "Sensor.h"
#include "Definition.h"

class SpeedChanger : public Sensor
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;
public:
	//! Default constructor
	SpeedChanger();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	SpeedChanger(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Sets angular damping change
	/*!
	\param damp new dynamic entities' angular damping
	*/
	void SetAngDamp(float damp);
	//! Sets linear damping change
	/*!
	\param damp new dynamic entities' linear damping
	*/
	void SetLinDamp(float damp);
	//! Returns current angular damping
	/*!
	\returns angular damping
	*/
	float getAngDamp();
	//! Returns current linear damping
	/*!
	\returns linear damping
	*/
	float getLinDamp();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~SpeedChanger();
};