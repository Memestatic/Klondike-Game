#include "Pile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Stack.h"

#include <string>

Pile::Pile() {

};

Pile::Pile(float RectangleX, float RectangleY, std::string stackType) : Stack(0, width, height, stackType) {
	Shape.setPosition(pos_X, pos_Y);
	Shape.setSize(sf::Vector2f(this->width, this->height));
	Shape.setFillColor(Color::Transparent);
	Shape.setOutlineColor(Color(169, 169, 169));
	Shape.setOutlineThickness(3);
	this->stackType = stackType;
};

void Pile::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->Shape, state);
}

void Pile::setType(std::string type) {
	this->Type = type;
}

std::string Pile::getType() {
	return this->Type;
}

std::string Pile::getStackType(){
	return this->stackType;
}
