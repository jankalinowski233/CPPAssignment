#include "TextureManager.h"

bool TextureManager::m_instanceFlag = false;
TextureManager* TextureManager::texSingleton = nullptr;

bool TextureManager::addTexture(std::string key, std::string fileName)
{
	//has this texture already been loaded?
	if (m_texMap.find(key) != m_texMap.end()) return false;
	
	//can the file be opened?
	sf::Texture tempTex;
	if (!tempTex.loadFromFile(fileName)) return false;
	
	//add texture
	m_texMap[key] = new sf::Texture(tempTex);
	return true;
}

sf::Texture * TextureManager::getTexture(std::string key) const
{
	auto it = m_texMap.find(key);
	if (it != m_texMap.end()) return it->second;
	return nullptr;
}

TextureManager* TextureManager::getInstance()
{
	if (m_instanceFlag == false)
	{
		texSingleton = new TextureManager();
		m_instanceFlag = true;
		return texSingleton;
	}
	else
	{
		return texSingleton;
	}
}

TextureManager::~TextureManager()
{
	m_instanceFlag = false;
	delete texSingleton;

	for (auto& pair : m_texMap) delete pair.second;
	m_texMap.clear();
}
