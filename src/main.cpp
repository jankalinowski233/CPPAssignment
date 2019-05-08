/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Game.h"

#include <iostream>

#define _CRTDBG_MAP_ALLOC 

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Box2D golf"); // Open main window

	float fFrameTime = 1.f / 60.f;

	// Start a clock to provide time for the physics
	sf::Clock clock;

	LevelLoader *levelLoader = levelLoader->getInstance();

	levelLoader->loadSounds();
	levelLoader->loadTextures();

	Game *game = game->getInstance();

	game->LoadNextLevel();

	// Run a game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) 
			{
				//enable debug
				if (event.key.code == sf::Keyboard::Tab)
				{
					game->ToggleDebug();
				}

				//add force
				if (event.key.code == sf::Keyboard::Space)
				{
					float timer = clock.getElapsedTime().asMilliseconds();
					if (timer > fFrameTime)
					{
						game->AddBallForce();
					}
				}
			}

			//shoot ball
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					game->ShootBall();
				}
			}
			
			//grab mouse position
			if (event.type == sf::Event::MouseMoved) 
			{
				game->RotateBall(event, window);
			}

		}

		// Find out how much time has elapsed
		float m_fElapsedTime = clock.getElapsedTime().asSeconds();

		// If a frame has past the update the game
		if (m_fElapsedTime > fFrameTime)
		{
			game->update(m_fElapsedTime);
			game->finishGame(m_fElapsedTime, window);
			clock.restart();
		}

		window.clear(sf::Color(120, 120, 120));
		window.draw(*game);
		window.display();
	}

	_CrtDumpMemoryLeaks();

}