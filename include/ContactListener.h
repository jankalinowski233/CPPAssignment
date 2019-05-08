#pragma once

/*!
\file ContactListener.h
\class ContactListener
\brief Allows collision processing

Called when a collision occurs. Inherits from b2ContactListener.
*/

#include <Box2D/Box2D.h>
#include "StaticBlock.h"
#include "DynamicBlock.h"
#include "StaticCircle.h"
#include "DynamicCircle.h"
#include "StaticPolygon.h"
#include "Ball.h"

#include "RotatingBlock.h"
#include "SlidingDoor.h"
#include "Door.h"
#include "DoorOpener.h"
#include "Booster.h"
#include "SpeedChanger.h"
#include "Ramp.h"
#include "Hole.h"
#include "Star.h"
#include "UI.h"

#include "SoundManager.h"

class ContactListener : public b2ContactListener
{
private:
	//! Box2D pointer to first collided body
	b2Body* bodyA;
	//! Box2D pointer to second collided body
	b2Body* bodyB;
	//! Pair of data of first collided body
	std::pair<std::string, void*> pairA;
	//! Pair of data of second collided body
	std::pair<std::string, void*> pairB;

	//! Pointer to the ball
	Ball *b;
	//! Pointer to a movable block
	DynamicBlock *block;
	//! Pointer to a movable circle
	DynamicCircle *circle;
	//! Initial linear damping
	float originalLinDamp;
	//! Initial angular damping
	float originalAngDamp;

	//! Bool to controll whether ball has collided with something
	bool ballCollided = false;
	//! Bool to controll whether block has collided with something
	bool blockCollided = false;
	//! Bool to controll whether circle has collided with something
	bool circleCollided = false;

	//! Pointer to the user interface
	UserInterface *m_ui;
	//! Instance of texture manager
	TextureManager *m_texManager = m_texManager->getInstance();

	//! Instance of sound manager
	SoundManager *m_soundManager = m_soundManager->getInstance();
	//! Sound played on star collection
	sf::Sound starSound;
	//! Sound played on reaching the goal
	sf::Sound score;
	//! Sound played on obstacle hit
	sf::Sound obHit;
	//! Sound played on boost
	sf::Sound boost;
	//! Sound played on button press
	sf::Sound button;
public:
	//! Default constructor
	ContactListener();
	//! Happens when contact begins
	/*!
	/param contact Called when two bodies begin to touch
	*/
	void BeginContact(b2Contact* contact);
	//! Happens when contact ends
	/*!
	\param contact Called when two bodies finish touching
	*/
	void EndContact(b2Contact* contact);
	//! Happens before change of momentum
	/*!
	\param contact Before change of momentum
	\param oldMf holds data about both bodies before change of momentum
	*/
	void PreSolve(b2Contact* contact, const b2Manifold* oldMf);
	//! Happens after change of momentum
	/*!
	\param contact After change of momentum
	\param impulse change of momentum
	*/
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	//! Sets user interface
	void setUI(UserInterface *ui);
	//! Destructor
	~ContactListener();

	//! Pointer to ramp object
	Ramp *r;
};