#pragma once

/*!
\file Game.h
\class Game
\brief Main game behaviour processing point

Contains general game mechanics, input processing and its results. Inherits from sf::Drawable.
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <vector>

#include "Shape.h"
#include "Ball.h"
#include "SFMLDebugDraw.h"

#include "Ray.h"
#include "ContactListener.h"
#include "UI.h"
#include "SoundManager.h"
#include "TextureManager.h"

#include "Booster.h"
#include "SpeedChanger.h"
#include "SlidingDoor.h"

class Game : public sf::Drawable
{
private:
	//! Main view
	sf::View m_view;
	//! UI view
	sf::View UI;
	//! Size of the world
	sf::Vector2f m_worldSize = sf::Vector2f(8.f, 8.f);

	//! Instance of texture manager
	TextureManager *m_texManager = m_texManager->getInstance();
	//! SFML's rectangle shape - background image
	sf::RectangleShape background;

	//! Initial ball force
	float force = 0.f;
	//! Maximum ball force
	float maxForce = 0.1f;
	
	//! End game timer
	float finishTimer = 0.f;
	//! Current level
	int levelIndex = -1;
	//! Bool to check if there's next level to load
	bool nextLevelExists;

	//! Bool to check whether ball is moving
	bool isRolling = false;
	//! Initial length of the ray
	float rayLength = 0.f;

	//! Bool to enable debug mode
	bool m_debug = false;
	//! Debug mode
	SFMLDebugDraw debug;

	//! Box2D's world pointer
	b2World * m_pWorld = nullptr;
	//! Box2D's velocity iterations
	const int mk_iVelIterations = 7;
	//! Box2D's position iterations
	const int mk_iPosIterations = 5;
	//! Box2D's world's gravity
	const b2Vec2 m_kGravity = b2Vec2(0.0f, 0.f);

	//! Ray cast forwards from the ball
	Ray ray;
	//! Contact listener to enable collision processing
	ContactListener m_listener;
	//! User interface displaying information to users
	UserInterface ui;

	//! Instance of sound manager
	SoundManager *m_soundManager = m_soundManager->getInstance();
	//! Sound played on shooting the ball
	sf::Sound ballHit;

	//! Bool to check if instance of an object already exists
	static bool m_instanceFlag;
	//! Pointer to itself; singleton pattern
	static Game *gameSingleton;
	//! Default constructor
	Game();
public:
	//! Updates all events and entities' positions in the game. Happens once each frame.
	/*!
	\param fTimestep time between updates
	*/
	void update(float fTimestep);
	//! Enables debug mode
	void ToggleDebug();
	//! Draws all shapes and ray
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Adds linear impulse to the force
	void AddBallForce();
	//! Applies linear impulse to the ball
	void ShootBall();
	//! Moves the camera
	/*!
	\param time time between position update
	*/
	void moveView(float time);
	//! Rotates balls towards mouse position
	/*!
	\param e reference to SFML's event
	\param w reference to SFML's window
	*/
	void RotateBall(sf::Event &e, sf::RenderWindow &w);
	//! Loads level; starts at the levelIndex of 0.
	void LoadNextLevel();
	//! Finishes game
	/*!
	\param time time before closing window
	\param w reference to SFML's window
	*/
	void finishGame(float time, sf::RenderWindow &w);
	//! Returns world instance
	/*!
	\returns world
	*/
	b2World* getWorld();
	//! Deletes all entities from the game
	void ClearLevel();
	//! Gets current level index
	/*!
	\returns levelIndex
	*/
	int getLevelIndex();
	//! Returns itself; singleton pattern
	/*!
	\returns instance of Game
	*/
	static Game* getInstance();
	//! Destructor
	~Game();

	//! Vector of static shapes
	std::vector<StaticShape*> m_stShapes;
	//! Vector of kinematic shapes
	std::vector<KinematicShape*> m_kShapes;
	//! Vector of dynamic shapes
	std::vector<DynamicShape*> m_dShapes;
	//! Vector of sliding doors
	std::vector<SlidingDoor*> m_slidingDoors;
	//! Vector of stars
	std::vector<Star*> m_stars;
	//! Ball instance
	Ball* m_balls;
};
