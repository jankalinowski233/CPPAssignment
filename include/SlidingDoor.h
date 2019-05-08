#pragma once

/*!
\file SlidingDoor.h
\class SlidingDoor
\brief Creates sliding door

Holds general data about the sliding door and provides its functionality. Inherits from KinematicShape.
*/

#include "Shape.h"
#include "Definition.h"

class SlidingDoor : public KinematicShape
{
private:
	//! SFML's rectangle shape
	sf::RectangleShape shape;
	//! Door ID. Opens the correct door.
	int m_doorID;

	//! Timer
	float m_fTime;
	//! Maximum timer
	float m_fMotionTime;
	//! \enum m_doorState current door state	
	enum m_doorState { 
		CLOSED, //!< CLOSED state
		OPEN, //!< OPEN state
		CLOSING, //!< CLOSING state
		OPENING //!< OPENING state
		} state; //!< enum's shorthand name
public:
	//! Default constructor
	SlidingDoor();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param def pointer to Definition class
	*/
	SlidingDoor(b2World *world, Definition *def);
	//! Sets id
	/*!
	\param id new ID
	*/
	void setID(int id);
	//! Gets ID
	/*!
	\returns door's id
	*/
	int getID();
	//! Updates entity's position
	/*!
	\param timestep time between position updates
	*/
	void update(float timestep);
	//! Opens door
	/*!
	\param force Speed and direction of opening the door
	*/
	void open(float force);
	//! Sets user data used with collisions
	void SetUserData();
	//! Changes door states
	void changeDoorState();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~SlidingDoor();

};