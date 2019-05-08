#include "LevelLoader.h"

#include <iostream>

bool LevelLoader::m_instanceFlag = false;
LevelLoader* LevelLoader::loaderSingleton = nullptr;

LevelLoader::LevelLoader()
{
	
}

void LevelLoader::loadTextures()
{
	//load textures
	texManager->addTexture("ball", "./Assets/Textures/ball.jpg"); //https://www.shutterstock.com/pl/search/golf+ball+texture?studio=1
	texManager->addTexture("wood", "./Assets/Textures/wood.jpg"); //https://stmed.net/wallpaper-24645
	texManager->addTexture("star", "./Assets/Textures/star.jpg"); //http://worldartsme.com/google-stars-clipart.html#gal_post_84169_google-stars-clipart-1.jpg
	texManager->addTexture("cobble", "./Assets/Textures/cobble.jpg"); //https://www.textures.com/browse/streets/97701
	texManager->addTexture("steel", "./Assets/Textures/steel.jpg"); //https://www.vecteezy.com/free-vector/metal-texture
	texManager->addTexture("metal", "./Assets/Textures/metal.jpg"); //https://www.vecteezy.com/vector-art/174402-metal-texture
	texManager->addTexture("arrow", "./Assets/Textures/arrow.png"); //http://worldartsme.com/arrow-designs-clipart.html#gal_post_100205_arrow-designs-clipart-1.jpg
	texManager->addTexture("ramp", "./Assets/Textures/ramp.jpg"); //https://pixabay.com/illustrations/arrow-texture-background-pattern-894106/
	texManager->addTexture("sand", "./Assets/Textures/sand.jpg"); //https://es.3dexport.com/free-3dmodel-dosch-textures-sand-ground-sample-120289.htm
	texManager->addTexture("brick", "./Assets/Textures/brick.jpg"); //https://polycount.com/discussion/138244/creating-good-normal-map-from-2d-texture
	texManager->addTexture("ice", "./Assets/Textures/ice.jpg"); //https://3docean.net/category/cg-textures/ice
	texManager->addTexture("rubber", "./Assets/Textures/rubber.jpg"); //https://www.pinterest.es/pin/54043264257160579/?lp=true
	texManager->addTexture("grass", "./Assets/Textures/grass.jpg"); //https://creativemarket.com/hhh316/247499-Lush-Seamless-Grass-Texture
	texManager->addTexture("buttonOff", "./Assets/Textures/buttonRed.png"); //made myself
	texManager->addTexture("buttonOn", "./Assets/Textures/buttonGreen.png"); //made myself
	
	//bind texture manager
	stDef.setTexManager();
	kDef.setTexManager();
	dDef.setTexManager();
	dBall.setTexManager();
}

void LevelLoader::loadSounds()
{
	//load sounds
	soundManager->addSound("star", "./Assets/Sounds/star.wav"); //https://opengameart.org/content/512-sound-effects-8-bit-style
	soundManager->addSound("obHit", "./Assets/Sounds/obHit.wav"); //https://opengameart.org/content/512-sound-effects-8-bit-style
	soundManager->addSound("boost", "./Assets/Sounds/boost.wav"); //https://opengameart.org/content/512-sound-effects-8-bit-style
	soundManager->addSound("button", "./Assets/Sounds/button.wav"); //https://opengameart.org/content/512-sound-effects-8-bit-style
	soundManager->addSound("victory", "./Assets/Sounds/victory.wav"); //http://soundbible.com/1823-Winning-Triumphal-Fanfare.html
	soundManager->addSound("ballHit", "./Assets/Sounds/Swing.wav"); //https://www.freesoundeffects.com/free-sounds/golf-10105/
}

bool LevelLoader::loadLevel(Game * g, std::string fileName)
{
	std::ifstream myFile;
	myFile.open(fileName, std::ios_base::in);

	std::stringstream stringStream;
	std::string line;

	std::string type;
	const std::string empty = " ";

	shapeFactory.setWorld(g->getWorld());

	StaticShape *stShape;
	KinematicShape *kShape;
	DynamicShape *dShape;
	SlidingDoor *door;
	Star *s;
	Ball *ball;

	//can the file be opened?
	if (myFile.is_open())
	{
		//while file can be read
		while (std::getline(myFile, line))
		{	
			line.append(empty);
			stringStream.str(line);
			stringStream >> type;

			//static shapes
			if (type == "StaticBlock")
			{
				stDef.initStaticBlock(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}
			if (type == "StaticPolygon")
			{
				stDef.initStaticPolygon(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}
			if (type == "StaticCircle")
			{
				stDef.initStaticCircle(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}

			if (type == "Booster")
			{
				stDef.initBooster(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}
			
			if (type == "SpeedChanger")
			{
				stDef.initSpeedChanger(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}
			
			if (type == "Ramp")
			{
				stDef.initRamp(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}

			if (type == "Hole")
			{
				stDef.initHole(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}

			if (type == "DoorOpener")
			{
				stDef.initDoorOpener(type, stringStream);
				stShape = shapeFactory.makeStaticShape(&stDef);
				g->m_stShapes.push_back(stShape);
			}

			//kinematic shapes
			if (type == "RotatingBlock")
			{
				kDef.initRotatingBlock(type, stringStream);
				kShape = shapeFactory.makeKinematicShape(&kDef);
				g->m_kShapes.push_back(kShape);
			}

			if (type == "SlidingDoor")
			{
				kDef.initSlidingDoor(type, stringStream);
				door = shapeFactory.makeDoor(&kDef);
				g->m_slidingDoors.push_back(door);
			}

			if (type == "Star")
			{
				if (g->m_stars.size() < 5)
				{
					kDef.initStar(type, stringStream);
					s = shapeFactory.makeStar(&kDef);
					g->m_stars.push_back(s);
				}
			}

			//dynamic shapes
			if (type == "DynamicBlock")
			{
				dDef.initDynamicBlock(type, stringStream);
				dShape = shapeFactory.makeDynamicShape(&dDef);
				g->m_dShapes.push_back(dShape);
			}

			if (type == "DynamicCircle")
			{
				dDef.initDynamicCircle(type, stringStream);
				dShape = shapeFactory.makeDynamicShape(&dDef);
				g->m_dShapes.push_back(dShape);
			}

			if (type == "Door")
			{
				dDef.initDoor(type, stringStream);
				dShape = shapeFactory.makeDynamicShape(&dDef);
				g->m_dShapes.push_back(dShape);
			}

			//ball
			if (type == "Ball")
			{
				dBall.initBall(type, stringStream);
				ball = shapeFactory.makeBall(&dBall);
				g->m_balls = ball;
			}
		}

		myFile.close();
		return true;
	}
	return false;
}

LevelLoader * LevelLoader::getInstance()
{
	if(m_instanceFlag == false)
	{
		loaderSingleton = new LevelLoader();
		m_instanceFlag = true;
		return loaderSingleton;
	}
	else
	{
	return loaderSingleton;
	}
}

LevelLoader::~LevelLoader()
{
	delete loaderSingleton;
	loaderSingleton = nullptr;
	m_instanceFlag = false;
}
