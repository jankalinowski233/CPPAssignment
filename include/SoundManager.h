#pragma once

/*!
\file SoundManager.h
\class SoundManager
\brief Manages sounds

Using the map data structure stores the sounds. Gets them by looking for the key associated
with sounds.
*/

#include <SFML/Audio.hpp>
#include <map>

class SoundManager
{
private:
	//! Map of sounds
	std::map<std::string, sf::SoundBuffer*> m_soundMap;

	//! Bool to check if instance of an object already exists
	static bool m_instanceFlag;
	//! Pointer to itself; singleton pattern
	static SoundManager *soundSingleton;
	//! Default constructor
	SoundManager() {};
public:
	//! Adds sounds
	/*!
	\param key name of the sound
	\param fileName sound's file path
	\returns true if successful
	*/
	bool addSound(std::string key, std::string fileName);
	//! Returns sound
	/*!
	\param key name of the sound
	\returns sound
	*/
	sf::SoundBuffer *getSound(std::string key) const;
	//! Returns instance of itself; singleton pattern
	/*!
	\returns instance of SoundManager
	*/
	static SoundManager* getInstance();
	//! Destructor
	~SoundManager();
};