#pragma once

/*!
\file UI.h
\class UserInterface
\brief Creates user interface

Creates UI, which displays some information to the user, such as amount of applied force and amount of collected stars. 
Inherits from sf::Drawable.
*/

#include <SFML/Graphics.hpp>
#include "Star.h"

#include <string>
#include <vector>

class UserInterface : public sf::Drawable
{
private:
	//! SFML's view
	sf::View m_UIview;
	//! World size
	sf::Vector2f m_worldSize;

	//! Text's font
	sf::Font textFont;
	
	//! Object of a star
	Star s;
	//! Position of star's sprite in UI view
	sf::Vector2f starPos = sf::Vector2f(360.f, -325.f);
	//! Vector of Star's sprites
	std::vector<Star> m_stars;

	//! Vector of texts
	std::vector<sf::Text> texts;

	//! SFML's rectangle shape - outline of force bar
	sf::RectangleShape forceBarOutline;
	//! SFML's rectangle shape - actual force bar
	sf::RectangleShape forceBar;
public:
	//! Default constructor
	UserInterface();
	//! Adds collected star to UI view
	void addStar();
	//! Creates UI
	void createUI();
	//! Deletes stars from m_stars and resets UI stars initial position
	void ClearStars();
	//! Sets new force bar size, which corresponds to amount of force applied to the ball
	/*!
	\param size new force bar's size
	*/
	void setForceBarSize(sf::Vector2f size);
	//! Sets view
	/*!
	\param view new view
	*/
	void setView(sf::View view);
	//! Sets texts
	/*!
	\param i text's index from vector
	\param t new text
	*/
	void setText(int i, std::string t);
	//! Returns text
	/*!
	\param i text's index from vector
	*/
	sf::Text getText(int i);
	//! Returns view
	/*!
	\returns UI view
	*/
	sf::View getView();
	//! Draws geometry
	/*!
	\param target target to draw
	\param states states used for drawing the target
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Destructor
	~UserInterface();
};