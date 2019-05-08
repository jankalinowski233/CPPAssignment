#include "Game.h"
#include "LevelLoader.h"

#include <fstream>
#include <iostream>

bool Game::m_instanceFlag = false;
Game* Game::gameSingleton = nullptr;

LevelLoader *loader = loader->getInstance();

Game::Game()
{
	//create views
	m_view.setCenter(0, 0);
	m_view.setSize(m_worldSize);
	m_view.setViewport(sf::FloatRect(0.f, 0.f, 0.9f, 0.9f));

	ui.setView(m_view);
	ui.createUI();

	//bind listener
	m_listener.setUI(&ui);

	//create background image
	background.setTexture(m_texManager->getTexture("grass"));
	background.setSize(sf::Vector2f(m_worldSize.x + 5.f, m_worldSize.y + 5.f));
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(m_view.getCenter());

	//create world
	m_pWorld = new b2World(m_kGravity);
	m_pWorld->SetContactListener(&m_listener);
	debug.setWorld(m_pWorld);

	//create raycast
	ray = Ray(m_pWorld, sf::Color::Red);
	rayLength = m_worldSize.x + m_worldSize.y;

	//set sound buffer
	ballHit.setBuffer(*m_soundManager->getSound("ballHit"));

}

void Game::update(float fTimestep)
{
	m_pWorld->Step(fTimestep, mk_iVelIterations, mk_iVelIterations);

	m_balls->update();

	for (DynamicShape* dShapes : m_dShapes)
	{
		dShapes->update();

		if (dShapes->OnRamp() == true)
		{
			dShapes->ApplyForce(m_listener.r->GetSpeedModifier());
		}
	}

	for (SlidingDoor* doors : m_slidingDoors) doors->update(fTimestep);
	for (KinematicShape* kShapes : m_kShapes) kShapes->update();
	for (Star* s : m_stars) s->update();

	if (m_debug) debug.clear();

	//only cast ray if ball is idle
	if (m_balls->getBody()->GetLinearVelocity().x == 0.f && m_balls->getBody()->GetLinearVelocity().y == 0.f)
	{
		isRolling = false;
		ray.cast(m_balls->getPosition(), m_balls->getAngle() * Deg2Rad, rayLength);
	}

	//only apply force if ball is on ramp
	if (m_balls->isOnRamp == true)
	{
		m_balls->ApplyForce(m_listener.r->GetSpeedModifier());
	}

	//move view with the ball
	moveView(fTimestep);
}

void Game::ToggleDebug()
{
	m_debug = !m_debug;
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw main game view
	target.setView(m_view);
	target.draw(background);

	for (KinematicShape* kShapes : m_kShapes) target.draw(*kShapes);
	for (SlidingDoor* doors : m_slidingDoors) target.draw(*doors);
	for (StaticShape* sShapes : m_stShapes) target.draw(*sShapes);
	for (DynamicShape* dShapes : m_dShapes) target.draw(*dShapes);
	for (Star* s : m_stars) target.draw(*s);

	//draw ball
	target.draw(*m_balls);

	if (isRolling == false)
	{
		target.draw(ray);
	}

	if (m_debug) target.draw(debug);

	//draw ui
	target.draw(ui);
}

void Game::AddBallForce()
{
	//only allow adding force if ball is idle
	if (isRolling == false) 
	{
		force += 0.01f;
		if (force > maxForce) force = maxForce;
		ui.setForceBarSize(sf::Vector2f(force * 2000, 40.f));
	}
}

void Game::ShootBall()
{
	//only allow shooting ball if ball is idle
	if (isRolling == false)
	{
		m_balls->ApplyLinearImpulse(force);
		ballHit.play();
		force = 0.f;
		ui.setForceBarSize(sf::Vector2f(0.f, 0.5f));
	}
	isRolling = true;
}

void Game::moveView(float time)
{
	sf::Vector2f tempVec = m_balls->getPosition();
	sf::Vector2f direction = tempVec - m_view.getCenter();

	float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));

	if (magnitude >= 2.75f)
	{
		direction = direction / magnitude;
		m_view.move(direction * time * (magnitude / 1.5f));
		background.setPosition(m_view.getCenter());
	}
}

void Game::RotateBall(sf::Event &e, sf::RenderWindow &w)
{
	//only rotate if ball is idle
	if (isRolling == false)
	{
		sf::Vector2i mousePos = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
		sf::Vector2f mouseScreenPos = w.mapPixelToCoords(mousePos, m_view);
		m_balls->ApplyRotation(mouseScreenPos);
		ray.cast(m_balls->getPosition(), m_balls->getAngle() * Deg2Rad, rayLength);
	}
}

void Game::LoadNextLevel()
{
	//increase level index
	levelIndex++;
	
	//open file
	std::ifstream file;
	std::string filePath = "./Assets/Levels/Level" + std::to_string(getLevelIndex()) + ".txt";
	file.open(filePath);

	//can the file be opened?
	if (file.is_open())
	{
		//does next level exist?
		if (levelIndex > 0)
		{
			ui.setText(2, "SCORE");
			nextLevelExists = true;
			
		}
		//if the game has just been opened
		else
		{
			loader->loadLevel(this, "./Assets/Levels/Level" + std::to_string(getLevelIndex()) + ".txt");
		}
	}
	//file doesn't exist -- no next level, exit game.
	else
	{
		ui.setText(2, "VICTORY");
		nextLevelExists = false;
	}
	
}

void Game::finishGame(float time, sf::RenderWindow &w)
{
	if (m_balls->scored == true)
	{
		//increase timer
		finishTimer += time;

		//load next level
		if (nextLevelExists == true)
		{
			if (finishTimer >= 5)
			{
				ClearLevel();
				ui.ClearStars();
				loader->loadLevel(this, "./Assets/Levels/Level" + std::to_string(getLevelIndex()) + ".txt");
				m_view.setCenter(m_balls->getPosition());
				//reset text
				ui.setText(2, "");
				//reset timer
				finishTimer = 0;
			}
		}

		//exit game
		else
		{
			if (finishTimer >= 5)
			{
				w.close();
			}
		}
		
	}
}

b2World * Game::getWorld()
{
	return m_pWorld;
}

void Game::ClearLevel()
{
	for (StaticShape* sShapes : m_stShapes)
	{
		delete sShapes;
		sShapes = nullptr;
	}
	for (DynamicShape* dShapes : m_dShapes)
	{
		delete dShapes;
		dShapes = nullptr;
	}
	for (SlidingDoor* doors : m_slidingDoors)
	{
		delete doors;
		doors = nullptr;
	}
	for (KinematicShape* kShapes : m_kShapes)
	{
		delete kShapes;
		kShapes = nullptr;
	}
	for (Star* s : m_stars)
	{
		delete s;
		s = nullptr;
	}

	delete m_balls;
	m_balls = nullptr;

	//clear vectors
	m_stShapes.clear();
	m_dShapes.clear();
	m_slidingDoors.clear();
	m_kShapes.clear();
	m_stars.clear();
}

int Game::getLevelIndex()
{
	return levelIndex;
}

Game * Game::getInstance()
{
	if (m_instanceFlag == false)
	{
		gameSingleton = new Game();
		m_instanceFlag = true;
		return gameSingleton;
	}
	else
	{
		return gameSingleton;
	}
}

Game::~Game()
{
	//cleanup the memory
	delete gameSingleton;
	gameSingleton = nullptr;
	m_instanceFlag = false;

	delete m_pWorld;
	m_pWorld = nullptr;

	ClearLevel();
}
