/*****************************************************************//**
 * \file   Card.h
 * \brief  Card class
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextureManager.h"

using namespace sf;

class Card : public sf::Drawable {
	/** Card index (0-51) */
	int index;
	/** Card value (1-13) */
	int Value;
	/** Card color */
	std::string Color;
	/** Card type */
	std::string Type;
	/** Path to card's texture */
	std::string texturePath;
	/** Card shape (SFML) */
	RectangleShape cardShape;
	/** Card width (x) */
	float width = 65;
	/** Card height (y) */
	float height = 90;
	/** Card visibility variable */
	bool hidden;
	/** Card position (x) */
	float currentPositionX;
	/** Card position (y) */
	float currentPositionY;
public:
	/** Card basic constructor */
	Card();
	/** Card constructor */
	Card(int index, int value, std::string Color, std::string Type, std::string texturePath);
	/** Card destructor */
	~Card() = default;
	/** Card draw (SFML) method */
	void draw(RenderTarget& target, RenderStates state) const override;
	/** Card possitioning method */
	void setPosition(float X, float Y);
	/** Getting card position method */
	std::pair<float, float> getPosition();
	/** Setting texture method */
	void setTexture();
	/** Getting card shape method (SFML feature) */
	RectangleShape getShape();
	/** Getting card ID method */
	int getId();
	/**
	 * Setting card visibility method.
	 * 
	 * \param i Hidden variable
	 */
	void setHidden(const bool i);
	/** Getting card visibility method */
	bool getHidden();
	/** Getting card value method */
	int getValue();
	/** Getting card color method */
	std::string getColor();
	/** Getting card type method */
	std::string getType();
	/** Setting outline of card shape method */
	void setOutline();
};

//1-A
//2-2
//3-3
//4-4
//5-5
//6-6
//7-7
//8-8
//9-9
//10-10
//11-J
//12-Q
//13-K

