/*****************************************************************//**
 * \file   Stack.h
 * \brief  Stack class, heap and pile classes inherit from this class.
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include "Card.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Stack : public sf::Drawable{
	/** Type of stack (stack / pile / heap). Implemented to differentiate different stacks in program. */
	std::string stackType;
public:
	/** Stack ID */
	int id;
	/** Vector of cards assigned to that stack */
	std::vector<Card> cards;
	/** Shape of the stack (SFML) */
	RectangleShape Shape;
	/** Stack position (x) */
	float pos_X;
	/** Stack position (y) */
	float pos_Y;
	/** Stack width (x) */
	const float width = 60;
	/** Stack height (y) */
	const float height = 90;
	/**
	 * Stack constructor.
	 * 
	 * \param number Stack ID
	 * \param RectangleX Stack position (x)
	 * \param RectangleY Stack position (y)
	 * \param stackType Stack type
	 */
	Stack(const int number, float RectangleX, float RectangleY, std::string stackType);
	/** Stack basic constructor */
	Stack();
	/** Stack destructor */
	~Stack() = default;
	/** Virtual drawing method (SFML) */
	void virtual draw(RenderTarget& target, RenderStates state) const override;
	/**
	 * Virtual setting position method.
	 * 
	 * \param x X
	 * \param y Y
	 */
	void virtual setPos(float x, float y);
	/**
	 * Adding card to stack's vector method.
	 * 
	 * \param card Card
	 */
	void virtual addCard(Card card);
	/**
	 * Removing x cards from the back of stack's vector method.
	 * 
	 * \param number Number of cards we want to remove
	 */
	void virtual removeCards(int number);
	/** Removing first cards from vector method */
	void virtual removeFirstCard();
	/** Method returning last card in stack's vector */
	Card virtual returnLastCard();
	/** Getting position of stack (x,y) */
	std::pair<float, float> getPos();
	/**
	 * Method that defines if card is last in stack's vector
	 * 
	 * \param card Card
	 */
	bool isLastInStack(Card& card);
	/** Method that returnes index of last card in stack's vector */
	int returnCardInStackIndex(int card);
	/** Getting stack's shape method (SFML) */
	RectangleShape getShape();
	/** Getting stack type method */
	std::string getStackType();
};


