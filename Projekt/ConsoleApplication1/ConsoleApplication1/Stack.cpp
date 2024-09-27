#include "Stack.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Klondike.h"


Stack::Stack() {
    // Konstruktor domyœlny
}

Stack::Stack(int number, float pos_X, float pos_Y, std::string stackType) : id(id), pos_X(pos_X), pos_Y(pos_Y) {
    Shape.setPosition(pos_X, pos_Y);
    Shape.setSize(sf::Vector2f(this->width, this->height));
    Shape.setFillColor(sf::Color::Transparent);
    Shape.setOutlineColor(sf::Color(169, 169, 169));
    Shape.setOutlineThickness(3);
    this->stackType = stackType;
}

void Stack::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(Shape, state);
}

void Stack::setPos(float x, float y) {
    this->pos_X = x;
    this->pos_Y = y;
    Shape.setPosition(x, y);
}

std::pair<float, float> Stack::getPos() {
    return std::make_pair(this->pos_X, this->pos_Y);
}

void Stack::addCard(Card card) {
    this->cards.push_back(card);
}

void Stack::removeCards(int number) {
    for(int i=0; i<number;i++){
        this->cards.pop_back();
    }
}

void Stack::removeFirstCard(){
    this->cards.erase(this->cards.begin());
}

Card Stack::returnLastCard(){
    return this->cards[this->cards.size() - 1];
}

bool Stack::isLastInStack(Card& card){
    if (card.getId() == this->cards[this->cards.size() - 1].getId())
        return true;
    else
        return false;
}

int Stack::returnCardInStackIndex(int id) {
    for (int i = 0; i < this->cards.size(); i++) {
        if (this->cards[i].getId() == id) {
            return i;
        }
    }
}

RectangleShape Stack::getShape() {
    return this->Shape;
};

std::string Stack::getStackType() {
    return this->stackType;
}
