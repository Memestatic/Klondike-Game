#include "Shuffle.h"
#include "Card.h"

#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;



std::vector<Card> Shuffle::GenerateDeck() {
	std::vector<Card> Deck;
	int k = 0;
	for (int i = 1; i <= 13; i++) {
		std::string j = std::to_string(i);
		Card card1(k, i, "Black", "Clubs", j +"_1.png");
		k++;
		Card card2(k, i, "Red", "Diamonds", j + "_2.png");
		k++;
		Card card3(k, i, "Red", "Hearts", j + "_3.png");
		k++;
		Card card4(k, i, "Black", "Spades", j + "_4.png");
		k++;
		Deck.push_back(card1);
		Deck.push_back(card2);
		Deck.push_back(card3);
		Deck.push_back(card4);
	}
	return Deck;
};

std::vector<Card> Shuffle::ShuffleDeck(std::vector<Card> Deck) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(seed);
	std::shuffle(Deck.begin(), Deck.end(), engine);
	return Deck;
};
