#include "SoundManager.h"
#include <iostream>

bool SoundManager::m_instanceFlag = false;
SoundManager* SoundManager::soundSingleton = nullptr;

bool SoundManager::addSound(std::string key, std::string fileName)
{
	//has this sound already been loaded?
	if (m_soundMap.find(key) != m_soundMap.end()) return false;

	//can the file be opened?
	sf::SoundBuffer tempSound;
	if (!tempSound.loadFromFile(fileName))
	{
		std::cout << "failed" << std::endl;
		return false;
	}

	//add sound
	m_soundMap[key] = new sf::SoundBuffer(tempSound);
	return true;
}

sf::SoundBuffer * SoundManager::getSound(std::string key) const
{
	auto it = m_soundMap.find(key);
	if (it != m_soundMap.end())
	{
		return it->second;
	}
	
	return nullptr;
}

SoundManager * SoundManager::getInstance()
{
	if (m_instanceFlag == false)
	{
		soundSingleton = new SoundManager();
		m_instanceFlag = true;
		return soundSingleton;
	}
	else
	{
		return soundSingleton;
	}
}

SoundManager::~SoundManager()
{
	m_instanceFlag = false;
	delete soundSingleton;

	for (auto& pair : m_soundMap) delete pair.second;
	m_soundMap.clear();
}
