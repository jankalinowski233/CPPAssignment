#pragma once

/*!
\file Star.h
\class Star
\brief Creates star

Holds general data about the star and provides its functionality. Stars can be collected by
a player. Inherits from Sensor.
*/

#include "Shape.h"
#include "Definition.h"

class Star : public KinematicShape
{
private:
	//! Instance of TextureManager
	TextureManager *m_texManager;
	//! SFML's rectangle shape
	sf::RectangleShape shape;
	//! Rotation speed
	float angVelocity;
	//! Bool to controll whether a is collected by a player
	bool deletionFlag = false;
	//! Pointer to the texture
	sf::Texture *tex;
public:
	//! Default constructor
	Star();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	Star(b2World *world, Definition *def);
	//! Sets user data used with collisions
	void SetUserData();
	//! Updates entity's position
	void update();
	//! Creates a star as a part of the UI after collection
	/*!
	\param pos star's position in UI view
	*/
	void createUIStar(sf::Vector2f pos);
	//! Deletes star
	void DeleteStar();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~Star();
};