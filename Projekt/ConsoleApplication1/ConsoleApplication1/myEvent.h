/*****************************************************************//**
 * \file   myEvent.h
 * \brief  Class made to enable undoing movements. Named myEvent because Event already exists as a part of SFML library.
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include "Card.h"
#include "Stack.h"
#include "Pile.h"
#include "Heap.h"

class myEvent {
	/** Event type */
	int type;
	/** Amount of cards that are being moved from stack to stack */
	int movedCardsAmount;
	/** Grabbed stack pointer (stack from which card/s were moved) */
	Stack* grabbedStackPtr;
	/** Destination card place (by reference) */
	Card destinationCard;
	/** Destination stack pointer */
	Stack* destinationStackPtr;
	/** Variable that defines if moving any card uncovered card below it */
	bool changedTexture;
public:
	/** Event basic constructor */

	~myEvent();
	myEvent();
	/**
	 * Event constructor.
	 * 
	 * \param type Amount of cards that are being moved from stack to stack
	 * \param movedCardsAmount Grabbed stack pointer (stack from which card/s were moved)
	 * \param grabbedStackPtr Grabbed stack pointer (stack from which card/s were moved)
	 * \param destinationCard Destination card place (by reference)
	 * \param destinationStackPtr Destination stack pointer
	 */
	myEvent(int type, int movedCardsAmount, Stack* grabbedStackPtr, Card& destinationCard, Stack* destinationStackPtr);
	/**
	 * Event constructor.
	 *
	 * \param type Amount of cards that are being moved from stack to stack
	 * \param movedCardsAmount Grabbed stack pointer (stack from which card/s were moved)
	 * \param grabbedStackPtr Grabbed stack pointer (stack from which card/s were moved)
	 * \param destinationStackPtr Destination stack pointer
	 */
	myEvent(int type, int movedCardsAmount, Stack* grabbedStackPtr, Stack* destinationStackPtr);
	/**
	 * Event constructor.
	 *
	 * \param type Amount of cards that are being moved from stack to stack
	 * \param movedCardsAmount Grabbed stack pointer (stack from which card/s were moved)
	 */
	myEvent(int type, int movedCardsAmount);
	/** Getting event type method */
	int getType();
	/** Getting amount of moved cards method */
	int getMovedCardsAmount();
	/** Getting pointer to grabbed stack method */
	Stack* getGrabbedStackPtr();
	/** Getting destination card method */
	Card getDestinationCard();
	/** Getting pointer to destination stack method */
	Stack* getDestinationStackPtr();
	/** Getting changedTexture variable */
	bool getChangedTexture();
	/**
	 * Setting changedTexture variable.
	 * 
	 * \param x ChangedTexture variable
	 */
	void setChangedTexture(bool x);
};


//Types
//1-Card To Stack
//2-Cards to Stack
//3-King to Stack
//4-King and more cards from Stack to Stack
//5-Ace to Pile
//6-Cards to Pile
//7-empty heap1
//8-card to heap2
