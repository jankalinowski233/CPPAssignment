#pragma once

/*!
\file Shape.h
\brief Basis file to all entities
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalEntity.h"

/*!
\class ShapeInterface
\brief Basis class to all entities

Abstract class.
*/
class ShapeInterface
{
public:
	//! Pure virtual function setting user data
	virtual void SetUserData() = 0;
};

/*!
\class StaticShape
\brief Basis class to all static shapes.

Inherits from sf::Drawable, PhysicalEntity and ShapeInterface.
*/
class StaticShape : public sf::Drawable, public PhysicalEntity, ShapeInterface
{
protected:

public:
	//! Pure virtual function setting user data
	virtual void SetUserData() = 0;
};

/*!
\class KinematicShape
\brief Basis class to all kinematic shapes

Inherits from sf::Drawable, PhysicalEntity and ShapeInterface.
*/
class KinematicShape : public sf::Drawable, public PhysicalEntity, ShapeInterface
{
protected:
public:
	//! Virtual update
	virtual void update() {};
	//! Pure virtual SetUserData
	virtual void SetUserData() = 0;
};

/*!
\class DynamicShape
\brief Basis class to all dynamic shapes

Inherits from sf::Drawable, PhysicalEntity and ShapeInterface.
*/
class DynamicShape : public sf::Drawable, public PhysicalEntity, ShapeInterface
{
protected:
	//! onRamp Bool to check whether a dynamic shape has collided with ramp
	bool onRamp = false;
public:
	//! Virtual update
	virtual void update() {};
	//! Virtual ApplyForce
	/*!
	\param force constant force to apply
	*/
	virtual void ApplyForce(b2Vec2 force) {};
	//! Virtual onRamp. Returns true if shape is on ramp.
	virtual bool OnRamp() { return onRamp; }
	//! Pure virtual SetUserData
	virtual void SetUserData() = 0;
	//! Virtual getOriginalLinDamp
	/*!
	\returns initial linear damping
	*/
	virtual float getOriginalLinDamp() { return 0.f; };
	//! Virtual getOriginalAngDamp
	/*!
	\returns initial angular damping
	*/
	virtual float getOriginalAngDamp() { return 0.f; };
};