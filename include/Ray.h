#pragma once

/*!
\file Ray.h
\class Ray
\brief Casts ray

Inherits from sf::Drawable.
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ray : public sf::Drawable
{
private:
	//! Pointer to Box2D's world
	b2World * m_pWorld;
	//! Line of the ray
	sf::VertexArray m_line;
public:
	//! Default constructor
	Ray();
	//! Custom constructor
	/*!
	\param world pointer to Box2D world
	\param colour new colour of the ray
	*/
	Ray(b2World* world, sf::Color colour);
	//! Casts ray
	/*!
	\param start starting point
	\param direction direction of cast
	\param maxLength maximum length of the ray
	*/
	void cast(sf::Vector2f start, float direction, float maxLength);
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};