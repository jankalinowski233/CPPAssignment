#pragma once

/*!
\file Definition.h
\class Definition
\brief Loads entities attributes

Reads file and loads the attributes (e.g. size or textures) of shapes. Basic class for other definitions
*/

#include <string>
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Definition
{
public:
	//! Instance of TextureManager
	TextureManager *m_texManager;
	//! String stream from file
	std::stringstream sStream;

	//! Type of an entity
	std::string type;
	//! Texture key
	std::string texName;
	//! Texture
	sf::Texture *texture;

	//! Position of an entity
	sf::Vector2f pos;
	//! Size of rectangulars entities
	sf::Vector2f size;

	//! Boost strength
	b2Vec2 boost;
	//! Force strength
	b2Vec2 force;

	//! Initial orientation of an entity
	float fOrientation;
	//! Velocity of e.g. rotation
	float speedModifier;
	//! Position of vertices in StaticPolygon
	float polygonExtents;
	//! Radius of circular entities
	float fRadius;
	//! Initial angular damping
	float fAngularDamping;
	//! Initial linear damping
	float fLinearDamping;
	//! SlidingDoor id
	float id;

	//! R value of a colour
	int rColour;
	//! G value of a colour
	int gColour;
	//! B value of a colour
	int bColour;

	//! Colour of the entity
	sf::Color m_colour;

	//! Default constructor
	Definition() {};

	//! TextureManager setter
	void setTexManager() { m_texManager = m_texManager->getInstance(); };

	//! Reads and returns float
	/*!
	\returns a number
	*/
	float getFloat()
	{
		float a;
		sStream >> a;
		return a;
	};

	//! Reads RGB values and returns colour
	/*!
	\returns a colour
	*/
	sf::Color getColor()
	{
		int rColour;
		int gColour;
		int bColour;

		sStream >> rColour;
		sStream >> gColour;
		sStream >> bColour;

		return sf::Color(rColour, gColour, bColour);
	};

	//! Reads 2 floats and returns SFML's vector
	/*!
	\returns an SFML's vector
	*/
	sf::Vector2f getVector()
	{
		float x;
		float y;
		
		sStream >> x;
		sStream >> y;

		return sf::Vector2f(x, y);
	};
	
	//! Reads 2 floats and returns Box2D's vector
	/*!
	\returns a Box2D's vector
	*/
	b2Vec2 getb2Vec()
	{
		float x;
		float y;

		sStream >> x;
		sStream >> y;

		return b2Vec2(x, y);
	}

	//! Returns initial type of an entity
	/*!
	\returns type of shape
	*/
	std::string getType()
	{
		return type;
	}

	//! Reads texture name and finds it
	/*!
	\returns a texture
	*/
	sf::Texture *getTexture()
	{
		sStream >> texName;
		return m_texManager->getTexture(texName);
	}
};

/*!
\class StaticShapeDefinition
\brief Creates static entities from file

Inherits from Definition
*/
class StaticShapeDefinition : public Definition
{
private:
	
public:
	//! Default constructor
	StaticShapeDefinition();
	//! Creates static block
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initStaticBlock(std::string initialType, std::stringstream& s);
	//! Creates static polygon
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initStaticPolygon(std::string initialType, std::stringstream& s);
	//! Creates static circle
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initStaticCircle(std::string initialType, std::stringstream& s);
	//! Creates booster
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initBooster(std::string initialType, std::stringstream& s);
	//! Creates field that increases or decreases angular and/or linear damping
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initSpeedChanger(std::string initialType, std::stringstream& s);
	//! Creates ramp
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initRamp(std::string initialType, std::stringstream& s);
	//! Creates goal
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initHole(std::string initialType, std::stringstream& s);
	//! Creates button to open SlidingDoor
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initDoorOpener(std::string initialType, std::stringstream& s);
};

/*!
\class KinematicShapeDefinition
\brief Creates kinematic entities from file

Inherits from Definition
*/
class KinematicShapeDefinition : public Definition
{
private:
public:
	//! Default constructor
	KinematicShapeDefinition();
	//! Creates rotating block
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initRotatingBlock(std::string initialType, std::stringstream& s);
	//! Creates sliding door
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initSlidingDoor(std::string initialType, std::stringstream& s);
	//! Creates star
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initStar(std::string initialType, std::stringstream& s);
};

/*!
\class DynamicShapeDefinition
\brief Creates dynamic entities from file

Inherits from Definition
*/
class DynamicShapeDefinition : public Definition
{
private:
public:
	//! Default constructor
	DynamicShapeDefinition();
	//! Creates dynamic block
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initDynamicBlock(std::string initialType, std::stringstream& s);
	//! Creates dynamic circle
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initDynamicCircle(std::string initialType, std::stringstream& s);
	//! Creates hittable door
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initDoor(std::string initialType, std::stringstream& s);
};

/*!
\class BallDefinition
\brief Creates ball from file

Inherits from Definition
*/
class BallDefinition : public Definition
{
private:
public:
	//! Default constructor
	BallDefinition();
	//! Creates ball
	/*!
	\param initialType type of an entity
	\param s reference to stringstream from a file
	*/
	void initBall(std::string initialType, std::stringstream& s);
};