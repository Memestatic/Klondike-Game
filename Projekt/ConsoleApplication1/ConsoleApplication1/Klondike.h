/*****************************************************************//**
 * \file   Klondike.h
 * \brief  Main Game Class
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include <vector>
#include <string>
#include "Klondike.h"
#include "Stack.h"
#include "Pile.h"
#include "Heap.h"
#include "Shuffle.h"
#include "myEvent.h"
#include "TextureManager.h"
#include "Card.h"
#include "Player.h"

class Klondike {
public:
	/** Static variable - X and Y of screen */
	static std::pair<float, float> screenSize;
	/** Menu choice variable */
	static std::string choice;
	/** Logged player object */
	static Player player;
	/** Player login */
	static std::string login;
	/** Player password */
	static std::string password;
	/** Player saved record */
	static int record;
	/** Record time of won game by the player */
	static std::string timeRecord;
	/** Whole Game Method */
	static void Game();
	/** Displaying menu method */
	static void Menu();
	/** Player registering method */
	static void Register();
	/** Player logging method */
	static bool Login(std::string& loginPlayer, std::string& passwordPlayer, int& record, std::string& timeRecord);
	/** Setting new player's record method */
	static void setRecord(Player& player);
	/** Displaying tutorial method */
	static void Tutorial();
	/** Creating stacks method */
	static std::vector<Stack> stacks();
	/** Creating piles method */
	static std::vector<Pile> piles();
	/** Creating heaps method */
	static std::vector<Heap> heaps();
	/** Creating differents coords / values being used in program. They are dependent of the screen size. */
	static std::vector<float> coords();
	/**
	 * Starting cards positioning method.
	 * 
	 * \param stacks Stacks vector
	 * \param piles Piles vector
	 * \param heaps Heaps vector
	 * \param cards Cards vector
	 * \param coords Coords vector
	 */
	static void setCards(std::vector<Stack> &stacks, std::vector<Pile> &piles, std::vector<Heap> &heaps, std::vector<Card> &cards, std::vector<float>& coords);
};
