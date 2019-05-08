#pragma once

/*!
\file TextureManager.h
\class TextureManager
\brief Manages textures

Using the map data structure stores the textures. Gets them by looking for the key associated
with textures.
*/

#include <SFML/Graphics.hpp>
#include <map>

class TextureManager
{
private:
	//! Map of textures
	std::map<std::string, sf::Texture*> m_texMap;

	//! Bool to check if instance of an object already exists
	static bool m_instanceFlag;
	//! Pointer to itself; singleton pattern
	static TextureManager *texSingleton;
	//! Default constructor
	TextureManager() {};
public:
	//! Adds textures
	/*!
	\param key name of the texture
	\param fileName texture's file path
	\returns true if successful
	*/
	bool addTexture(std::string key, std::string fileName);
	//! Returns a texture
	/*!
	\param key name of the texture
	\returns texture
	*/
	sf::Texture *getTexture(std::string key) const;
	//! Returns instance of itself; singleton pattern
	/*!
	\returns instance of TextureManager
	*/
	static TextureManager* getInstance();
	//! Destructor
	~TextureManager();
};