#include "UI.h"

#include <iostream>

UserInterface::UserInterface()
{
}

void UserInterface::addStar()
{
	//create star in the UI view
	s.createUIStar(starPos);
	starPos.y += 75.f;
	m_stars.push_back(s);
}

void UserInterface::createUI()
{
	//load font
	textFont.loadFromFile("./Assets/Fonts/Rocks Personal Use.ttf");

	//create force bar
	forceBar.setPosition(-275.f, 340.f);
	setForceBarSize(sf::Vector2f(0.f, 40.f));

	forceBarOutline.setFillColor(sf::Color(0, 0, 0, 255.f));
	forceBarOutline.setPosition(-275.f, 340.f);
	forceBarOutline.setSize(sf::Vector2f(200.f, 40.f));
	forceBarOutline.setOutlineThickness(3.f);
	forceBarOutline.setOutlineColor(forceBarOutline.getFillColor());

	//create texts
	texts.resize(3);
	
	for (auto& t : texts)
	{
		t.setFont(textFont);
	}
	
	texts[0].setString("Stars");
	texts[1].setString("Force");
	texts[2].setString("");

	texts[0].setCharacterSize(55);
	texts[1].setCharacterSize(60);
	texts[2].setCharacterSize(250);

	texts[0].setFillColor(sf::Color::White);
	texts[1].setFillColor(sf::Color::White);
	texts[2].setFillColor(sf::Color::Yellow);

	texts[0].setPosition(325.f, -420.f);
	texts[1].setPosition(-370.f, 315.f);
	texts[2].setPosition(-250.f, -200.f);
}

void UserInterface::ClearStars()
{
	//reset position
	starPos = sf::Vector2f(360.f, -325.f);
	//clear vector
	m_stars.clear();
}

void UserInterface::setForceBarSize(sf::Vector2f size)
{
	forceBar.setSize(size);
}

void UserInterface::setView(sf::View view)
{
	m_UIview.setCenter(view.getCenter());
	m_UIview.setSize(sf::Vector2f(800, 800));
	m_UIview.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

void UserInterface::setText(int i, std::string t)
{
	texts[i].setString(t);
}

sf::Text UserInterface::getText(int i)
{
	return texts[i];
}

sf::View UserInterface::getView()
{
	return m_UIview;
}

void UserInterface::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//set different view
	target.setView(m_UIview);
	
	for (Star s : m_stars)
	{
		target.draw(s);
	}

	for (auto& t : texts)
	{
		target.draw(t);
	}

	target.draw(forceBarOutline);
	target.draw(forceBar);
}

UserInterface::~UserInterface()
{
	ClearStars();
}
