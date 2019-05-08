#include "pch.h"

#define private public

#include "Game.h"
#include "LevelLoader.h"
#include "Ball.h"
#include "ShapeFactory.h"
#include "Definition.h"
#include "SlidingDoor.h"

Game *game;

using namespace std;

TEST(GameTest, DebugModeTest)
{
	bool debugBefore = game->m_debug;
	game->ToggleDebug();
	bool debugAfter = game->m_debug;

	EXPECT_NE(debugBefore, debugAfter);
}

TEST(GameTest, AddForce)
{
	float tempForceBefore = game->force;
	game->force += 0.02f;
	float tempForceAfter = game->force;

	EXPECT_NE(tempForceBefore, tempForceAfter);
}

TEST(GameTest, CreatePlayer)
{
	Ball *b = nullptr;
	Ball *b2 = game->m_balls;

	EXPECT_NE(b, b2);
}

TEST(GameTest, EndGame)
{
	Ball *b = game->m_balls;
	bool victoryConditionBefore = b->scored;
	b->scored = true;
	bool victoryConditionAfter = b->scored;

	EXPECT_NE(victoryConditionBefore, victoryConditionAfter);
}

TEST(BallTest, ShootBall)
{
	Ball *b = game->m_balls;
	b2Vec2 velBefore = b->getLinearVelocity();
	b->ApplyLinearImpulse(0.5f);
	b2Vec2 velAfter = b->getLinearVelocity();

	EXPECT_NE(velBefore, velAfter);
}

TEST(BallTest, RotateBall)
{
	Ball *b = game->m_balls;
	float angleBefore = b->angle;
	b->ApplyRotation(sf::Vector2f(0.5f, 0.5f));
	float angleAfter = b->angle;

	EXPECT_NE(angleBefore, angleAfter);
}

TEST(MechanicTest, OpenDoor)
{
	SlidingDoor *sDoor = new SlidingDoor();
	int stateBefore = sDoor->state;
	sDoor->state = sDoor->OPENING;
	int stateAfter = sDoor->state;

	sDoor = nullptr;
	delete sDoor;

	EXPECT_NE(stateBefore, stateAfter);
}

TEST(LoadingTest, OpenFile)
{
	std::ifstream file;
	file.open("./Assets/Levels/Level1.txt");
	EXPECT_TRUE(file.is_open());
}

TEST(LoadingTest, ReadFile)
{
	std::string stringBefore;
	std::ifstream file;
	file.open("./Assets/Levels/Level1.txt");
	std::stringstream sStream;
	std::string stringAfter;
	std::getline(file, stringAfter);
	sStream >> stringAfter;
	file.close();
	EXPECT_NE(stringBefore, stringAfter);
}

TEST(ResourceTest, AddTexture)
{
	TextureManager *texMan = texMan->getInstance();
	sf::Texture *tempTexBefore = nullptr;
	texMan->addTexture("ball", "./Assets/Textures/ball.jpg");
	sf::Texture *tempTexAfter = texMan->getTexture("ball");

	EXPECT_NE(tempTexBefore, tempTexAfter);
}

TEST(ResourceTest, AddSound)
{
	SoundManager *sMan = sMan->getInstance();
	sf::SoundBuffer *tempSoundBefore = nullptr;
	sMan->addSound("star", "./Assets/Sounds/star.wav");
	sf::SoundBuffer *tempSoundAfter = sMan->getSound("star");

	EXPECT_NE(tempSoundBefore, tempSoundAfter);
}

int main(int argc, char **argv) 
{
	LevelLoader *levelLoader = levelLoader->getInstance();

	levelLoader->loadSounds();
	levelLoader->loadTextures();

	game = game->getInstance();

	levelLoader->loadLevel(game, "./Assets/Levels/Level1.txt");

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}