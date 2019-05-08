#pragma once

/*!
\file DoorOpener.h
\class DoorOpener
\brief Creates button

Holds general data about the button and provides its functionality. Button may open 
sliding door if IDs are matched. Inherits from Sensor.
*/

#include "Sensor.h"
#include "Definition.h"

class DoorOpener : public Sensor
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;
	//! Button's id
	int m_id;
	//! Bool to control texture change
	bool m_texChanged = false;
public:
	//! Default constructor
	DoorOpener();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	DoorOpener(b2World *world, Definition *def);
	//! Opens door
	/*!
	\param id identifier to be matched
	*/
	void openDoor(int id);
	//! Sets id
	/*!
	\param id new identifier
	*/
	void setID(int id);
	//! Returns id
	/*!
	\returns button's ID
	*/
	int getID();
	//! Changes textures
	/*!
	\param tex new texture
	*/
	void changeTexture(sf::Texture *tex);
	//! Sets user data used with collisions
	void SetUserData();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~DoorOpener();
};