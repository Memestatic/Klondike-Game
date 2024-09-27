#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Klondike.h"
#include "Stack.h"
#include "Pile.h"
#include "Heap.h"
#include "Shuffle.h"
#include "myEvent.h"
#include "TextureManager.h"
#include "Card.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

using namespace sf;

std::string Klondike::choice;
std::pair<float, float> Klondike::screenSize;
std::string Klondike::login;
std::string Klondike::password;
int Klondike::record;
std::string Klondike::timeRecord;

void Klondike::Menu() {
	screenSize = std::make_pair(1280, 720);
	bool logged = false;
	int choiceInt;
	do {
		std::cout << "1.Play\n2.Register\n3.Login\n4.Tutorial\n5.Exit" << std::endl;
		std::cin >> choice;
		try {
			choiceInt = std::stoi(choice);
		}
		catch(std::exception& error){
			std::cout << "Wrong option!\n";
			break;
		}
		switch (choiceInt) {
		case 1:
			if (logged)
				Klondike::Game();
			else
				std::cout << "Log in first " << std::endl;
			break;
		case 2:
			Klondike::Register();
			break;
		case 3:
			logged = Klondike::Login(login, password, record, timeRecord);
			break;
		case 4:
			Klondike::Tutorial();
			break;
		case 5:
			std::cout << "Exit\n";
			break;
		default:
			std::cout << "Wrong option!\n";
			break;
		}
	} while (choiceInt != 5);
}

void Klondike::Game() {
	Player player(login, password, record, timeRecord);
	bool win = false;
	//////////////////////////////// Czas
	Clock clock;
	Time time;
	std::stringstream ss;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	Font font;
	font.loadFromFile("OpenSans-Regular.ttf");
	Text text("", font);
	text.setPosition(1100, 10);
	text.setCharacterSize(30);
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(2);

	//////////////////////////////// Rekordowy czas
	
	Text timeRecordText("Record time: ", font);
	timeRecordText.setPosition(1100, 150);
	timeRecordText.setCharacterSize(20);
	timeRecordText.setFillColor(Color::White);
	timeRecordText.setOutlineColor(Color::Black);
	timeRecordText.setOutlineThickness(2);

	Text timeRecordCounter(timeRecord, font);
	timeRecordCounter.setPosition(1100, 175);
	timeRecordCounter.setCharacterSize(20);
	timeRecordCounter.setFillColor(Color::White);
	timeRecordCounter.setOutlineColor(Color::Black);
	timeRecordCounter.setOutlineThickness(2);

	//////////////////////////////// Punkty
	 
	Text pointsText("Points: ", font);
	pointsText.setPosition(1100, 50);
	pointsText.setCharacterSize(20);
	pointsText.setFillColor(Color::White);
	pointsText.setOutlineColor(Color::Black);
	pointsText.setOutlineThickness(2);

	std::stringstream pts;
	Text pointsCounter("0", font);
	pointsCounter.setPosition(1100, 75);
	pointsCounter.setCharacterSize(20);
	pointsCounter.setFillColor(Color::White);
	pointsCounter.setOutlineColor(Color::Black);
	pointsCounter.setOutlineThickness(2);

	//////////////////////////////// Record

	Text recordText("Record: ", font);
	recordText.setPosition(1100, 100);
	recordText.setCharacterSize(20);
	recordText.setFillColor(Color::White);
	recordText.setOutlineColor(Color::Black);
	recordText.setOutlineThickness(2);

	Text recordCounter(std::to_string(player.getCurrentRecord()), font);
	recordCounter.setPosition(1100, 125);
	recordCounter.setCharacterSize(20);
	recordCounter.setFillColor(Color::White);
	recordCounter.setOutlineColor(Color::Black);
	recordCounter.setOutlineThickness(2);
	

	//////////////////////////////// Przycisk cofania

	RectangleShape undo;
	undo.setPosition(1196, 636);
	TextureManager::loadTexture("undo", "textures/undo.png");
	undo.setTexture(TextureManager::getTexture("undo"));
	undo.setSize(Vector2f(64, 64));
	
	//////////////////////////////// Gra

    std::vector<Stack> stacks = Klondike::stacks();
    std::vector<Pile> piles = Klondike::piles();
	std::vector<Heap> heaps = Klondike::heaps();
	std::vector<Card> cards = Shuffle::GenerateDeck();
	cards = Shuffle::ShuffleDeck(cards);
	std::vector<float> coords = Klondike::coords();
	std::vector<myEvent> myEvents;

    RenderWindow GameWindow(VideoMode(screenSize.first, screenSize.second), "Klondike");
	GameWindow.setFramerateLimit(60);
   
	TextureManager::loadTexture("background", "textures/greenbackground2.jpg");
	TextureManager::loadTexture("icon", "textures/icon.png");
	Image icon;
	icon.loadFromFile("textures/icon.png");
	GameWindow.setIcon(53, 53, icon.getPixelsPtr());
	Sprite s(*TextureManager::getTexture("background"));

	Event event;

	Klondike::setCards(stacks, piles, heaps, cards, coords); 

	int grabbedCardId = -1;
	Card* grabbedCardPtr = nullptr;
	Stack* grabbedStackPtr = nullptr;
	bool changedTexture = false;
	int movedCardsAmount = 0;
	while (GameWindow.isOpen())
	{

		//////////////////////////////// Rysowansko

		GameWindow.clear();
		GameWindow.draw(s);
		GameWindow.draw(text);
		GameWindow.draw(timeRecordText);
		GameWindow.draw(timeRecordCounter);
		GameWindow.draw(pointsText);
		GameWindow.draw(pointsCounter);
		GameWindow.draw(recordText);
		GameWindow.draw(recordCounter);
		GameWindow.draw(undo);
		//Stacks
		for (int i = 0; i < stacks.size(); i++) {
			GameWindow.draw(stacks[i]);
			for (int j = 0; j < stacks[i].cards.size(); j++) {
				GameWindow.draw(stacks[i].cards[j]);
			}
		}
		//Heaps
		for (int i = 0; i < heaps.size(); i++) {
			GameWindow.draw(heaps[i]);
			for (int j = 0; j < heaps[i].Stack::cards.size(); j++) {
				GameWindow.draw(heaps[i].Stack::cards[j]);
			}
		}
		//Piles
		for (int i = 0; i < piles.size(); i++) {
			GameWindow.draw(piles[i]);
			for (int j = 0; j < piles[i].Stack::cards.size(); j++) {
				GameWindow.draw(piles[i].Stack::cards[j]);
			}
		}

		GameWindow.display();

		////////////////////////////////

		while (GameWindow.pollEvent(event))
		{
			//////////////////////////////// Zamkniecie okna
			if (event.type == Event::Closed)
			{
				GameWindow.close();
			}
			//////////////////////////////// Obsluga klikniecia myszy
			
			
			
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {  
				Vector2f mousePosition = static_cast<Vector2f>(Mouse::getPosition(GameWindow));

				if (grabbedCardId == -1 && grabbedCardPtr == nullptr && grabbedStackPtr == nullptr) {
					//Sprawdzamy czy kliknieto karte na jakimkolwiek stosie
					bool end = false;
					for (Stack& i : stacks) {		
						for (int j = i.cards.size() - 1; j >= 0; j--) {
							RectangleShape shape = i.cards[j].getShape();
							if (shape.getGlobalBounds().contains(mousePosition) && i.cards[j].getHidden() == false) {
								grabbedCardId = i.cards[j].getId();
								grabbedCardPtr = &i.cards[j];
								grabbedStackPtr = &i;
								end = true;
								break;
							}
						}
						if (end)
							break;
					}
					end = false;
					//Sprawdzamy czy kliknieto karte na jakiejkolwiek stercie pile
					for (Pile& i : piles) {			
						for (int j = i.Stack::cards.size() - 1; j >= 0; j--) {
							RectangleShape shape = i.Stack::cards[j].getShape();
							if (shape.getGlobalBounds().contains(mousePosition) && i.Stack::cards[j].getHidden() == false) {
								grabbedCardId = i.Stack::cards[j].getId();
								grabbedCardPtr = &i.Stack::cards[j];
								grabbedStackPtr = &i;
								end = true;
								break;
							}
						}
						if (end)
							break;
					}
					//Sprawdzamy czy kliknieto karte na stercie Heap0
					if(heaps[0].Stack::cards.empty() == false){
						RectangleShape cardShape = heaps[0].Stack::cards[heaps[0].Stack::cards.size() - 1].getShape();
						if (cardShape.getGlobalBounds().contains(mousePosition)) {
							if (heaps[0].Stack::cards[heaps[0].Stack::cards.size() - 1].getHidden() == true) {
								heaps[0].Stack::cards[heaps[0].Stack::cards.size() - 1].setPosition(heaps[1].pos_X, heaps[1].pos_Y);
								heaps[0].Stack::cards[heaps[0].Stack::cards.size() - 1].setHidden(false);
								heaps[1].Stack::addCard(heaps[0].Stack::cards[heaps[0].Stack::cards.size() - 1]);
								heaps[0].Stack::cards.pop_back();
								myEvent event(8, 1);
								myEvents.push_back(event);
							}
						}
					}
					//Obslugujemy klikanie na drugiej stercie Heap1
					for (int i = heaps[1].Stack::cards.size() - 1; i >= 0; i--) {
						RectangleShape shape = heaps[1].Stack::cards[i].getShape();
						if (shape.getGlobalBounds().contains(mousePosition)) {
							grabbedCardId = heaps[1].Stack::cards[i].getId();
							grabbedCardPtr = &heaps[1].Stack::cards[i];
							grabbedStackPtr = &heaps[1];
							break;
						}
					}

					//Obslugujemy przycisk undo
					if (!myEvents.empty()) {
						int type = myEvents[myEvents.size() - 1].getType();
						Card undoGrabbedCard;
						Stack* undoGrabbedStackPtr = nullptr;
						Stack* undoDestinationStackPtr = nullptr;
						if (undo.getGlobalBounds().contains(mousePosition)) {
							switch (type) {
							case 1:
								undoGrabbedCard = myEvents[myEvents.size() - 1].getDestinationCard();
								undoGrabbedStackPtr = myEvents[myEvents.size() - 1].getDestinationStackPtr();
								undoDestinationStackPtr = myEvents[myEvents.size() - 1].getGrabbedStackPtr();
								changedTexture = myEvents[myEvents.size() - 1].getChangedTexture();
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								if (undoDestinationStackPtr != nullptr && undoGrabbedStackPtr!= nullptr) {
									if (undoDestinationStackPtr->getStackType() == heaps[1].getStackType()) {
										undoGrabbedCard.setPosition(heaps[1].Stack::pos_X, heaps[1].Stack::pos_Y);
										heaps[1].Stack::addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
									else if (undoDestinationStackPtr->getStackType() == stacks[0].getStackType()) {
										if (!undoDestinationStackPtr->cards.empty())
											undoGrabbedCard.setPosition(undoDestinationStackPtr->returnLastCard().getPosition().first, undoDestinationStackPtr->returnLastCard().getPosition().second + coords[6]);
										else
											undoGrabbedCard.setPosition(undoDestinationStackPtr->getPos().first, undoDestinationStackPtr->getPos().second);
										if (changedTexture) {
											player = player - 5;
											undoDestinationStackPtr->cards[undoDestinationStackPtr->cards.size() - 1].setHidden(true);
										}
										undoDestinationStackPtr->addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
									else if (undoDestinationStackPtr->getStackType() == piles[0].getStackType()) {
										undoGrabbedCard.setPosition(undoDestinationStackPtr->Stack::getPos().first, undoDestinationStackPtr->Stack::getPos().second);
										undoDestinationStackPtr->Stack::addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
										player = player + 10;
									}
								}
								else {
									std::cout << "Jedynka nie chce sie wykonac bo z jakiegos powodu te stosy sa nullptr" << std::endl;
								}
								break;
							case 2:
								undoGrabbedStackPtr = myEvents[myEvents.size() - 1].getDestinationStackPtr();
								undoDestinationStackPtr = myEvents[myEvents.size() - 1].getGrabbedStackPtr();
								changedTexture = myEvents[myEvents.size() - 1].getChangedTexture();
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								if (undoDestinationStackPtr != nullptr && undoGrabbedStackPtr != nullptr) {
									if (undoDestinationStackPtr->getStackType() == stacks[0].getStackType()) {
										if (changedTexture) {
											player = player - 5;
											undoDestinationStackPtr->cards[undoDestinationStackPtr->cards.size() - 1].setHidden(true);
										}
										for (int i = undoGrabbedStackPtr->cards.size() - movedCardsAmount; i < undoGrabbedStackPtr->cards.size(); i++) {
											if (!undoDestinationStackPtr->cards.empty())
												undoGrabbedStackPtr->cards[i].setPosition(undoDestinationStackPtr->returnLastCard().getPosition().first, undoDestinationStackPtr->returnLastCard().getPosition().second + coords[6]);
											else
												undoGrabbedStackPtr->cards[i].setPosition(undoDestinationStackPtr->getPos().first, undoDestinationStackPtr->getPos().second);
											undoDestinationStackPtr->addCard(undoGrabbedStackPtr->cards[i]);
										}
										undoGrabbedStackPtr->removeCards(movedCardsAmount);
										myEvents.pop_back();
									}
								}
								else {
									std::cout << "Dwojka nie chce sie wykonac bo z jakiegos powodu te stosy sa nullptr" << std::endl;
								}
								break;
							case 3:
								undoGrabbedCard = myEvents[myEvents.size() - 1].getDestinationCard();
								undoGrabbedStackPtr = myEvents[myEvents.size() - 1].getDestinationStackPtr();
								undoDestinationStackPtr = myEvents[myEvents.size() - 1].getGrabbedStackPtr();
								changedTexture = myEvents[myEvents.size() - 1].getChangedTexture();
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								if (undoDestinationStackPtr != nullptr && undoGrabbedStackPtr != nullptr) {
									if (undoDestinationStackPtr->getStackType() == heaps[1].getStackType()) {
										undoGrabbedCard.setPosition(heaps[1].Stack::pos_X, heaps[1].Stack::pos_Y);
										heaps[1].Stack::addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
									else if (undoDestinationStackPtr->getStackType() == stacks[0].getStackType()) {
										if (!undoDestinationStackPtr->cards.empty())
											undoGrabbedCard.setPosition(undoDestinationStackPtr->returnLastCard().getPosition().first, undoDestinationStackPtr->returnLastCard().getPosition().second + coords[6]);
										else
											undoGrabbedCard.setPosition(undoDestinationStackPtr->getPos().first, undoDestinationStackPtr->getPos().second);
										if (changedTexture) {
											player = player - 5;
											undoDestinationStackPtr->cards[undoDestinationStackPtr->cards.size() - 1].setHidden(true);
										}
										undoDestinationStackPtr->addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
									else if (undoDestinationStackPtr->getStackType() == piles[0].getStackType()) {
										undoGrabbedCard.setPosition(undoDestinationStackPtr->Stack::getPos().first, undoDestinationStackPtr->Stack::getPos().second);
										undoDestinationStackPtr->Stack::addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
								}
								else {
									std::cout << "Trojka nie chce sie wykonac bo z jakiegos powodu te stosy sa nullptr" << std::endl;
								}
								break;
							case 4:
								undoGrabbedStackPtr = myEvents[myEvents.size() - 1].getDestinationStackPtr();
								undoDestinationStackPtr = myEvents[myEvents.size() - 1].getGrabbedStackPtr();
								changedTexture = myEvents[myEvents.size() - 1].getChangedTexture();
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								if (undoDestinationStackPtr != nullptr && undoGrabbedStackPtr != nullptr) {
									if (undoDestinationStackPtr->getStackType() == stacks[0].getStackType()) {
										if (changedTexture) {
											player = player - 5;
											undoDestinationStackPtr->cards[undoDestinationStackPtr->cards.size() - 1].setHidden(true);
										}
										for (int i = undoGrabbedStackPtr->cards.size() - movedCardsAmount; i < undoGrabbedStackPtr->cards.size(); i++) {
											if (!undoDestinationStackPtr->cards.empty())
												undoGrabbedStackPtr->cards[i].setPosition(undoDestinationStackPtr->returnLastCard().getPosition().first, undoDestinationStackPtr->returnLastCard().getPosition().second + coords[6]);
											else
												undoGrabbedStackPtr->cards[i].setPosition(undoDestinationStackPtr->getPos().first, undoDestinationStackPtr->getPos().second);
											undoDestinationStackPtr->addCard(undoGrabbedStackPtr->cards[i]);
										}
										undoGrabbedStackPtr->removeCards(movedCardsAmount);
										myEvents.pop_back();
									}
								}
								else {
									std::cout << "Czworka nie chce sie wykonac bo z jakiegos powodu te stosy sa nullptr" << std::endl;
								}
								break;
							case 5:
								undoGrabbedCard = myEvents[myEvents.size() - 1].getDestinationCard();
								undoGrabbedStackPtr = myEvents[myEvents.size() - 1].getDestinationStackPtr();
								undoDestinationStackPtr = myEvents[myEvents.size() - 1].getGrabbedStackPtr();
								changedTexture = myEvents[myEvents.size() - 1].getChangedTexture();
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								if (undoDestinationStackPtr != nullptr && undoGrabbedStackPtr != nullptr) {
									if (undoDestinationStackPtr->getStackType() == heaps[1].getStackType()) {
										undoGrabbedCard.setPosition(heaps[1].Stack::pos_X, heaps[1].Stack::pos_Y);
										heaps[1].Stack::addCard(undoGrabbedCard);
										undoGrabbedStackPtr->Stack::cards.pop_back();
										myEvents.pop_back();
									}
									else if (undoDestinationStackPtr->getStackType() == stacks[0].getStackType()) {
										if (!undoDestinationStackPtr->cards.empty())
											undoGrabbedCard.setPosition(undoDestinationStackPtr->returnLastCard().getPosition().first, undoDestinationStackPtr->returnLastCard().getPosition().second + coords[6]);
										else
											undoGrabbedCard.setPosition(undoDestinationStackPtr->getPos().first, undoDestinationStackPtr->getPos().second);
										if (changedTexture) {
											player = player - 5;
											undoDestinationStackPtr->cards[undoDestinationStackPtr->cards.size() - 1].setHidden(true);
										}
										undoDestinationStackPtr->addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
								}
								else {
									std::cout << "Piatka nie chce sie wykonac bo z jakiegos powodu te stosy sa nullptr" << std::endl;
								}
								player = player - 10;
								break;
							case 6:
								undoGrabbedCard = myEvents[myEvents.size() - 1].getDestinationCard();
								undoGrabbedStackPtr = myEvents[myEvents.size() - 1].getDestinationStackPtr();
								undoDestinationStackPtr = myEvents[myEvents.size() - 1].getGrabbedStackPtr();
								changedTexture = myEvents[myEvents.size() - 1].getChangedTexture();
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								if (undoDestinationStackPtr != nullptr && undoGrabbedStackPtr != nullptr) {
									if(undoDestinationStackPtr->getStackType() == stacks[0].getStackType()) {
										if (!undoDestinationStackPtr->cards.empty())
											undoGrabbedCard.setPosition(undoDestinationStackPtr->returnLastCard().getPosition().first, undoDestinationStackPtr->returnLastCard().getPosition().second + coords[6]);
										else
											undoGrabbedCard.setPosition(undoDestinationStackPtr->getPos().first, undoDestinationStackPtr->getPos().second);
										if (changedTexture) {
											player = player - 5;
											undoDestinationStackPtr->cards[undoDestinationStackPtr->cards.size() - 1].setHidden(true);
										}
										undoDestinationStackPtr->addCard(undoGrabbedCard);
										undoGrabbedStackPtr->cards.pop_back();
										myEvents.pop_back();
									}
									else if (undoDestinationStackPtr->getStackType() == heaps[1].getStackType()) {
										undoGrabbedCard.setPosition(heaps[1].Stack::pos_X, heaps[1].Stack::pos_Y);
										heaps[1].Stack::addCard(undoGrabbedCard);
										undoGrabbedStackPtr->Stack::cards.pop_back();
										myEvents.pop_back();
									}
								}
								else {
									std::cout << "Szostka nie chce sie wykonac bo z jakiegos powodu te stosy sa nullptr" << std::endl;
								}
								player = player - 10;
								break;
							case 8:
								undoGrabbedStackPtr = nullptr;
								undoDestinationStackPtr = nullptr;
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								heaps[1].Stack::cards[heaps[1].Stack::cards.size() - 1].setPosition(heaps[0].Stack::pos_X, heaps[0].Stack::pos_Y);
								heaps[1].Stack::cards[heaps[1].Stack::cards.size() - 1].setHidden(true);
								heaps[0].Stack::addCard(heaps[1].Stack::cards[heaps[1].Stack::cards.size() - 1]);
								heaps[1].Stack::cards.pop_back();
								myEvents.pop_back();
								break;
							case 7:
								undoGrabbedStackPtr = nullptr;
								undoDestinationStackPtr = nullptr;
								movedCardsAmount = myEvents[myEvents.size() - 1].getMovedCardsAmount();
								std::reverse(heaps[0].Stack::cards.begin(), heaps[0].Stack::cards.end());
								heaps[1].Stack::cards = heaps[0].Stack::cards;
								heaps[0].Stack::cards.clear();
								for (Card& i : heaps[1].Stack::cards) {
									i.setPosition(heaps[1].Stack::getPos().first, heaps[1].Stack::getPos().second);
									i.setHidden(false);
								}
								player = player + 25;
								myEvents.pop_back();
								break;
							default:
								break;
							}
							undoGrabbedStackPtr = nullptr;
							undoDestinationStackPtr = nullptr;
						}
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
				Vector2f mousePosition = static_cast<Vector2f>(Mouse::getPosition(GameWindow));
				//Jesli karta chwycona, to czekamy na klikniecie zwalniajace karte na inny stos
				if (grabbedCardId != -1 && grabbedCardPtr != nullptr && grabbedStackPtr != nullptr) {
					for (Stack& i : stacks) {
						RectangleShape shape;
						if(!i.cards.empty())
							shape = i.cards[i.cards.size() - 1].getShape();
						RectangleShape stackShape = i.getShape();
						if (shape.getGlobalBounds().contains(mousePosition)) {
							if(i.cards[i.cards.size() - 1].getId() != grabbedCardId && !i.cards[i.cards.size() - 1].getHidden()) {						
								if(i.cards[i.cards.size() - 1].getValue() == (grabbedCardPtr->getValue())+1) {	//warunek wartosci
									if(i.cards[i.cards.size() - 1].getColor() != grabbedCardPtr->getColor()){	//warunek koloru
										if (grabbedStackPtr->isLastInStack(*grabbedCardPtr)) { //sprawdzamy czy przenosimy tylko jedn¹ kartê czy wieksza kupke kart
											//std::cout << "przenosimy jedna karte" << std::endl;
											grabbedCardPtr->setPosition(i.returnLastCard().getPosition().first, i.returnLastCard().getPosition().second + coords[6]);
											i.addCard(*grabbedCardPtr);
											grabbedStackPtr->cards.pop_back();
											myEvent event(1, 1, grabbedStackPtr, i.cards[i.cards.size() - 1], &i);
											if (!grabbedStackPtr->cards.empty()) {
												if (grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].getHidden() == true) {
													player = player + 5;
													event.setChangedTexture(true);
													grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].setHidden(false);		//odkrywamy karte spod przenoszonej karty
												}
											}
											myEvents.push_back(event);
											if (grabbedStackPtr->getStackType() == "pile") {
												player = player - 10;
											}
											break;
										}
										else {
											//std::cout << "przenosimy cala kupke kart" << std::endl;
											int x = grabbedStackPtr->returnCardInStackIndex(grabbedCardId);
											for (int k = x; k < grabbedStackPtr->cards.size(); k++) {
												grabbedStackPtr->cards[k].setPosition(i.returnLastCard().getPosition().first, i.returnLastCard().getPosition().second + coords[6]);
												i.addCard(grabbedStackPtr->cards[k]);
											}
											int cardsMoved = grabbedStackPtr->cards.size() - x;
											grabbedStackPtr->removeCards(grabbedStackPtr->cards.size() - x);
											myEvent event(2, cardsMoved, grabbedStackPtr, &i);
											if (!grabbedStackPtr->cards.empty()) {
												if (grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].getHidden() == true) {
													player = player + 5;
													grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].setHidden(false);		//odkrywamy karte spod przenoszonej karty
													event.setChangedTexture(true);
												}
											}
											myEvents.push_back(event);
											break;
										}
									}
								}
							}
						}
						else if (stackShape.getGlobalBounds().contains(mousePosition)) {	//Obslugujemy przenoszenie krola na pusty stos
							if(grabbedCardPtr->getValue() == 13){
								if (grabbedStackPtr->isLastInStack(*grabbedCardPtr)) { //sprawdzamy czy przenosimy tylko jedn¹ kartê czy wieksza kupke kart
									//std::cout << "przenosimy jedna karte" << std::endl;
									grabbedCardPtr->setPosition(i.pos_X, i.pos_Y);
									i.addCard(*grabbedCardPtr);
									grabbedStackPtr->cards.pop_back();
									myEvent event(3, 1, grabbedStackPtr, i.cards[i.cards.size() - 1], &i);
									if (!grabbedStackPtr->cards.empty()) {
										if (grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].getHidden() == true) {
											player = player + 5;
											grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].setHidden(false);		//odkrywamy karte spod przenoszonej karty
											event.setChangedTexture(true);
										}
									}
									myEvents.push_back(event);
									if (grabbedStackPtr->getStackType() == "pile") {
										player = player - 10;
									}
									break;
								}
								else {
									//std::cout << "przenosimy cala kupke kart" << std::endl;
									int x = grabbedStackPtr->returnCardInStackIndex(grabbedCardId);
									for (int k = x; k < grabbedStackPtr->cards.size(); k++) {
										grabbedStackPtr->cards[k].setPosition(i.pos_X, i.pos_Y + (k-x)*coords[6]);
										i.addCard(grabbedStackPtr->cards[k]);
									}
									int cardsMoved = grabbedStackPtr->cards.size() - x;
									grabbedStackPtr->removeCards(grabbedStackPtr->cards.size() - x);
									myEvent event(4, cardsMoved, grabbedStackPtr, &i);
									if (!grabbedStackPtr->cards.empty()) {
										if (grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].getHidden() == true) {
											player = player + 5;
											grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].setHidden(false);		//odkrywamy karte spod przenoszonej karty
											event.setChangedTexture(true);
										}
									}
									myEvents.push_back(event);
									break;
								}
							}
						}
					}
					//Obslugujemy przenoszenie kart na kupki piles
					for (Pile& i : piles) {
						if (i.Stack::cards.empty()) {
							RectangleShape pileShape = i.Stack::getShape();
							if (pileShape.getGlobalBounds().contains(mousePosition)) {
								if (grabbedStackPtr->isLastInStack(*grabbedCardPtr)) { // odkryta i na wierzchu stosu
									if (grabbedCardPtr->getValue() == 1) {		//tylko as
										if (grabbedCardPtr->getType() == i.getType()) {	//takie same typy
											grabbedCardPtr->setPosition(i.pos_X, i.pos_Y);
											player = player + 10;
											i.Stack::addCard(*grabbedCardPtr);
											grabbedStackPtr->cards.pop_back();
											myEvent event(5, 1, grabbedStackPtr, i.cards[i.cards.size() - 1], &i);
											if (!grabbedStackPtr->cards.empty()) {
												if (grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].getHidden() == true) {
													player = player + 5;
													grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].setHidden(false);		//odkrywamy karte spod przenoszonej karty
													event.setChangedTexture(true);
												}
											}
											myEvents.push_back(event);
											break;
										}
									}
								}
							}
						}
						else{		//Pile nie jest pusta, nie przenosimy asa a jakakolwiek inna karte
							RectangleShape cardShape = i.Stack::cards[i.Stack::cards.size() - 1].getShape();
							if (cardShape.getGlobalBounds().contains(mousePosition)) {
								if (grabbedStackPtr->isLastInStack(*grabbedCardPtr)) {					//karta na wierzchu stosu
									if (grabbedCardPtr->getValue() == i.Stack::cards[i.Stack::cards.size() - 1].getValue() + 1) {		//Mozna przelozyc karte o 1 wieksza
										if (grabbedCardPtr->getType() == i.getType()) {
											grabbedCardPtr->setPosition(i.pos_X, i.pos_Y);
											player = player + 10;
											i.Stack::addCard(*grabbedCardPtr);
											grabbedStackPtr->cards.pop_back();
											myEvent event(6, 1, grabbedStackPtr, i.cards[i.cards.size() - 1], &i);
											if (!grabbedStackPtr->cards.empty()) {
												if (grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].getHidden() == true) {
													player = player + 5;
													grabbedStackPtr->cards[grabbedStackPtr->cards.size() - 1].setHidden(false);		//odkrywamy karte spod przenoszonej karty
													event.setChangedTexture(true);
												}
											}
											myEvents.push_back(event);
											
											break;
										}
									}
								}
							}
						}
					}
					grabbedCardId = -1;
					grabbedCardPtr = nullptr;
					grabbedStackPtr = nullptr;
				}
				//Sprawdzamy czy kliknieto pusta sterte 1
				if (grabbedCardId == -1 && grabbedCardPtr == nullptr && grabbedStackPtr == nullptr) {
					if (heaps[0].Stack::cards.empty()) {
						RectangleShape heapShape = heaps[0].Stack::getShape();
						if (heapShape.getGlobalBounds().contains(mousePosition)) {
							//std::cout << "Empty heap clicked!" << std::endl;
							std::reverse(heaps[1].Stack::cards.begin(), heaps[1].Stack::cards.end());
							heaps[0].Stack::cards = heaps[1].Stack::cards;
							heaps[1].Stack::cards.clear();
							for (Card& i : heaps[0].Stack::cards) {
								i.setPosition(heaps[0].Stack::getPos().first, heaps[0].Stack::getPos().second);
								i.setHidden(true);
							}
							myEvent event(7, 1);
							myEvents.push_back(event);
							player = player - 25;
						}
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Middle) {
				///////
			}
        }
		//////////////////////////////// Czas
		
		ss.str("");
		time = clock.getElapsedTime();
		seconds = time.asSeconds();
		hours = seconds / 3600;
		minutes = (seconds - (hours * 3600)) / 60;
		seconds = seconds - (hours * 3600 + minutes * 60);
		if (hours < 10)
			ss << "0" << hours;
		else
			ss << hours;
		if (minutes < 10)
			ss << ":" << "0" << minutes;
		else
			ss << ":" << minutes;
		if (seconds < 10)
			ss << ":" << "0" << seconds;
		else
			ss << ":" << seconds;

		text.setString(ss.str());

		///////////////////////////////// Punkty
		ss.str("");
		ss << player.getPoints();
		pointsCounter.setString(ss.str());



		///////////////////////////////// Warunek Konca
		if (piles[0].Stack::cards.size() == 13 && piles[1].Stack::cards.size() == 13 && piles[2].Stack::cards.size() == 13 && piles[3].Stack::cards.size() == 13) {
			win = true;
			player.checkTimeRecord(timeRecordCounter, hours, minutes, seconds);
			auto playerPtr = std::make_unique<Player>(player);
			Klondike::setRecord(*playerPtr);
			break;
		}
    }


	///////////////////////////////////// Koniec gry
	if (win) {
		Event end;
		RenderWindow EndGame(VideoMode(260, 0), "Congratulations!");
		while (EndGame.isOpen()) {
			while (EndGame.pollEvent(end)) {
				if (end.type == Event::Closed)
				{
					EndGame.close();
					break;
				}
			}
		}
	}
	
}

std::vector<Stack> Klondike::stacks() {
	std::vector<float> coords = Klondike::coords();
	float x = coords[0];
	float y = coords[1];
	std::vector<Stack> stacks;
	int id = 0;
	for (int i = 0; i < 7; i++) {
		Stack stack1(i, x, y, "stack");
		stack1.setPos(x, y);
		stack1.id = id;
		stacks.push_back(stack1);
		x += screenSize.first/8.89;
		id++;
	}

	return stacks;
}

std::vector<Pile> Klondike::piles() {
	std::vector<float> coords = Klondike::coords();
	float x = coords[2];
	float y = coords[3];
	std::vector<Pile> piles;
	int id = 0;
	for (int i = 0; i < 4; i++) {
		Pile pile1(x, y, "pile");
		Stack* pp = &pile1;
		pp->setPos(x, y);
		pp->id = id;
		piles.push_back(pile1);
		x += screenSize.first /8.89;
		id++;
	}
	piles[0].setType("Clubs");
	piles[1].setType("Diamonds");
	piles[2].setType("Hearts");
	piles[3].setType("Spades");
	return piles;
}

std::vector<Heap> Klondike::heaps() {
	std::vector<float> coords = Klondike::coords();
	float x = coords[4];
	float y = coords[5];
	std::vector<Heap> heaps;
	int id = 0;
	for (int i = 0; i < 2; i++) {
		Heap heap(x, y, "heap");
		Stack* pp = &heap;
		pp->setPos(x, y);
		pp->id = id;
		heaps.push_back(heap);
		x += screenSize.first / 16;
		id++;
	}
	return heaps;
}

std::vector<float> Klondike::coords() {
	std::vector<float> coords;
	float stack_X = screenSize.first /6.15;
	float stack_Y = screenSize.second /2.22;
	float pile_X = screenSize.first /2.35;
	float pile_Y = screenSize.second /17.14;
	float heap_X = screenSize.second / 22.86;
	float heap_Y = screenSize.second / 17.14;
	float cardsYdiff = screenSize.second / 60;
	coords.push_back(stack_X);
	coords.push_back(stack_Y);
	coords.push_back(pile_X);
	coords.push_back(pile_Y);
	coords.push_back(heap_X);
	coords.push_back(heap_Y);
	coords.push_back(cardsYdiff);
	return coords;
};

void Klondike::setCards(std::vector<Stack> &stacks, std::vector<Pile> &piles, std::vector<Heap> &heaps, std::vector<Card> &cards, std::vector<float> &coords) {
	for (int i = 0; i < cards.size(); i++) {
		cards[i].setTexture();
	}
	for (int i = 0; i < 7; i++)
	{
		std::pair<float, float> posPair = stacks[i].getPos();
	    int cardsInStack = i + 1; // Liczba kart w danym stosie

	    for (int j = 0; j < cardsInStack; j++)
	    {
	        int cardIndex = (i * (i + 1)) / 2 + j; // Obliczanie indeksu karty w stosie
	        if (j == cardsInStack - 1) {
	            // Odkryta karta na wierzchu stosu
	            cards[cardIndex].setHidden(false);
	        }
	        else {
	            // Zakryta karta
	            cards[cardIndex].setHidden(true);
	        } 
	        cards[cardIndex].setPosition(posPair.first, posPair.second + coords[6]*j);
			stacks[i].addCard(cards[cardIndex]);
	    }
	}

	std::pair<float, float> posPair = heaps[0].getPos();
	for (int i = 28; i < cards.size(); i++) {
		cards[i].setPosition(posPair.first, posPair.second);
		heaps[0].Stack::addCard(cards[i]);
	}
	for (Card& i : heaps[0].Stack::cards) {
		i.setHidden(true);
	}
}

void Klondike::Register() {
	std::string login;
	std::string password;
	std::cout << std::endl << "Enter login: ";
	std::cin >> login;
	std::cout << std::endl << "Enter password: ";
	std::cin >> password;
	std::vector<std::string> data;
	std::ifstream file("users.txt");
	std::string line;
	bool exists = false;
	while (getline(file, line)) {
		std::stringstream ss;
		std::size_t end = line.find_first_of("%");
		std::string ucieta = line.substr(0, end);
		ss << ucieta;
		std::string word;
		while (ss >> word) {
			data.push_back(word);
		}
		if (data[0] == login) {
			exists = true;
			std::cout << "User with that login already exists!" << std::endl;
			break;
		}
		data.clear();
	}
	if (!exists) {
		std::ofstream file("users.txt", ios::app);
		std::stringstream ss;
		file << login << " " << password << " " << 0 << " " << 0 << " %" << "\n";
		std::cout << "Registration successful!" << std::endl;
	}
}

bool Klondike::Login(std::string& loginPlayer, std::string& passwordPlayer, int& record, std::string& timeRecord) {
	std::vector<std::string> data;
	std::cout << std::endl << "Enter login: ";
	std::cin >> login;
	std::cout << std::endl << "Enter password: ";
	std::cin >> password;
	std::ifstream file("users.txt");
	std::string line;
	while (getline(file, line)) {
		std::stringstream ss;
		std::size_t end = line.find_first_of("%");
		std::string ucieta = line.substr(0, end);
		ss << ucieta;
		std::string word;
		while (ss >> word) {
			data.push_back(word);
		}
		if (data[0] == login && data[1] == password) {
			loginPlayer = login;
			passwordPlayer = password;
			record = std::stoi(data[2]);
			timeRecord = data[3];
			std::cout << "Login succesfull! " << std::endl;
			return true;
		}
		else
			data.clear();
	}
	std::cout << "Try again" << std::endl;
	return false;
}

void Klondike::Tutorial(){
	std::ifstream file("Tutorial.txt");
	std::string str;
	std::cout << "--------------------" << std::endl;
	std::cout << "------Tutorial------" << std::endl;
	std::cout << "--------------------" << std::endl;
	while (std::getline(file, str)) {
		std::cout << str << std::endl;
	}
	std::cout << "--------------------" << std::endl;
}

void Klondike::setRecord(Player& player){
	if (player.getPoints() < 0) {
		player.setPoints(0);
	}
	if (player.getPoints() > player.getCurrentRecord()) {
		player.setCurrentRecord(player.getPoints());
	}
	std::string strReplace = player.getLogin() +" " + player.getPassword() + " " + std::to_string(record) + " " + timeRecord + " %";
	std::string strNew = player.getLogin() + " " + player.getPassword() + " " + std::to_string(player.getCurrentRecord()) + " " + player.getTimeRecord() + " %";
	std::ifstream filein("users.txt");
	std::ofstream fileout("fileout.txt");
	std::string strTemp;
	bool found = false;
	while (getline(filein, strTemp))
	{
		if (strTemp == strReplace) {
			strTemp = strNew;
			found = true;
		}
		fileout << strTemp;
		fileout << "\n";
		if (found) {
			break;
		}
	}
	filein.close();
	fileout.close();
	/*	Deletes the file if exists */
	std::remove("users.txt");
	if (std::rename("fileout.txt", "users.txt") != 0)
		perror("Error renaming file");
	else
		cout << "File renamed successfully";
}