#pragma once

/*!
\file LevelLoader.h
\class LevelLoader
\brief Loads level

Reads a file line by line, passes argument to Definition and creates entities in the game's world
*/

#include "Game.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "ShapeFactory.h"
#include "Definition.h"
#include <string>

#include <fstream>
#include <sstream>

class LevelLoader 
{
private:
	//! Definition of static shapes
	StaticShapeDefinition stDef;
	//! Definition of kinematic shapes
	KinematicShapeDefinition kDef;
	//! Definition of dynamic shapes
	DynamicShapeDefinition dDef;
	//! Definition of a ball
	BallDefinition dBall;
	//! ShapeFactory object
	ShapeFactory shapeFactory;
	//! Instance of TextureManager
	TextureManager *texManager = texManager->getInstance();
	//! Instance of SoundManager
	SoundManager *soundManager = soundManager->getInstance();

	//! Bool to check if instance of an object already exists
	static bool m_instanceFlag;
	//! Pointer to itself; singleton pattern
	static LevelLoader *loaderSingleton;
	//! Default constructor
	LevelLoader();
public:
	//! Loads textures
	void loadTextures();
	//! Loads sounds
	void loadSounds();
	//! Reads file and loads level
	/*!
	\param g pointer to the game instance
	\param fileName file path
	*/
	bool loadLevel(Game *g, std::string fileName);
	//! Returns itself; singleton pattern
	/*!
	\returns instance of Game
	*/
	static LevelLoader* getInstance();
	//! Destructor
	~LevelLoader();
};