#include "Ray.h"

#include <iostream>

Ray::Ray()
{
}

Ray::Ray(b2World * world, sf::Color colour)
{
	m_pWorld = world;

	m_line.setPrimitiveType(sf::Lines);
	m_line.resize(2);
	m_line[0].color = colour;
	m_line[1].color = colour;
}

void Ray::cast(sf::Vector2f start, float direction, float maxLength)
{
	//calculate ray direction and length
	b2Vec2 l_start = b2Vec2(start.x, start.y);
	b2Vec2 l_direction = b2Vec2(cosf(direction), sinf(direction));

	b2Vec2 p1 = l_start;
	b2Vec2 p2 = p1 + maxLength * l_direction;

	//cast ray
	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1;

	//look for the closest fixture in every body
	float closestFraction = 1;
	for (b2Body * body = m_pWorld->GetBodyList(); body; body = body->GetNext())
	{
		for (b2Fixture * fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			b2RayCastOutput output;
			if (!fixture->RayCast(&output, input, 1))
			{
				//std::cout << "Something went wrong with ray" << std::endl;
			}
			else if (output.fraction < closestFraction)
			{
				if (!fixture->IsSensor())
				{
					closestFraction = output.fraction;
				}
			}
		}
	}

	b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

	m_line[0].position = start;
	m_line[1].position = sf::Vector2f(intersectionPoint.x, intersectionPoint.y);
}

void Ray::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_line);
}