/*****************************************************************//**
 * \file   Shuffle.h
 * \brief  Class being used to generate and shuffle card deck
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include <vector>
#include "Card.h"

class Shuffle {
public:
	/** Generating deck method */
	static std::vector<Card> GenerateDeck();
	/**
	 * Shuffling deck method.
	 * 
	 * \param Deck Deck we want to shuffle
	 */
	static std::vector<Card> ShuffleDeck(std::vector<Card> Deck);
};