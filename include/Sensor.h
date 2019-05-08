#pragma once

/*!
\file Sensor.h
\class Sensor
\brief Base class for all sensors

Holds general data about the sensors. Inherits from StaticShape.
*/

#include "Shape.h"

class Sensor : public StaticShape
{
protected:
	//! Initial speed modifier
	b2Vec2 m_fModifier;

	//! Angular damping changer
	float fAngDamp; 
	//! Linear damping changer
	float fLinDamp;

public:
	//! Pure virtual function setting user data
	virtual void SetUserData() = 0;
	//! Virtual function changing velocity
	/*!
	\param modifier new velocity
	*/
	virtual void SetSpeedModifier(b2Vec2 modifier) { m_fModifier = modifier; };
	//! Virtual function returning current velocity changer
	/*!
	\returns speed modifier
	*/
	virtual b2Vec2 GetSpeedModifier() { return m_fModifier; };
};