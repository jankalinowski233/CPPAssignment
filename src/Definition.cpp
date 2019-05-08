#include "Definition.h"

StaticShapeDefinition::StaticShapeDefinition() {}
KinematicShapeDefinition::KinematicShapeDefinition() {}
DynamicShapeDefinition::DynamicShapeDefinition() {}
BallDefinition::BallDefinition() {}

void StaticShapeDefinition::initStaticBlock(std::string initialType, std::stringstream& s)
{
	type = initialType;

	sStream  << s.rdbuf();
	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	texture = getTexture();

}

void StaticShapeDefinition::initStaticPolygon(std::string initialType, std::stringstream& s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	polygonExtents = getFloat();
	fOrientation = getFloat();
	texture = getTexture();
}

void StaticShapeDefinition::initStaticCircle(std::string initialType, std::stringstream& s)
{
	type = initialType;

	sStream << s.rdbuf();
	pos = getVector();
	fRadius = getFloat();
	texture = getTexture();
}

void StaticShapeDefinition::initBooster(std::string initialType, std::stringstream& s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	boost = getb2Vec();
	texture = getTexture();
}

void StaticShapeDefinition::initSpeedChanger(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	fLinearDamping = getFloat();
	fAngularDamping = getFloat();
	texture = getTexture();
}

void StaticShapeDefinition::initRamp(std::string initialType, std::stringstream & s)
{
	type = initialType;
	
	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	force = getb2Vec();
	texture = getTexture();
}

void StaticShapeDefinition::initHole(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	fRadius = getFloat();

}

void StaticShapeDefinition::initDoorOpener(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	id = getFloat();
	texture = getTexture();
}

void DynamicShapeDefinition::initDoor(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	fAngularDamping = getFloat();
	texture = getTexture();
}

void KinematicShapeDefinition::initSlidingDoor(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	speedModifier = getFloat();
	id = getFloat();
	texture = getTexture();
}

void KinematicShapeDefinition::initStar(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	speedModifier = getFloat();
	texture = getTexture();
}

void KinematicShapeDefinition::initRotatingBlock(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();

	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	speedModifier = getFloat();
	texture = getTexture();
}

void DynamicShapeDefinition::initDynamicBlock(std::string initialType, std::stringstream& s)
{
	type = initialType;
	
	sStream << s.rdbuf();
	pos = getVector();
	size = getVector();
	fOrientation = getFloat();
	fAngularDamping = getFloat();
	fLinearDamping = getFloat();
	texture = getTexture();
}

void DynamicShapeDefinition::initDynamicCircle(std::string initialType, std::stringstream & s)
{
	type = initialType;
	
	sStream << s.rdbuf();
	pos = getVector();
	fRadius = getFloat();
	fOrientation = getFloat();
	fLinearDamping = getFloat();
	fAngularDamping = getFloat();
	texture = getTexture();
}

void BallDefinition::initBall(std::string initialType, std::stringstream & s)
{
	type = initialType;

	sStream << s.rdbuf();
	pos = getVector();
	fRadius = getFloat();
	fOrientation = getFloat();
	fAngularDamping = getFloat();
	fLinearDamping = getFloat();
	texture = getTexture();
}


