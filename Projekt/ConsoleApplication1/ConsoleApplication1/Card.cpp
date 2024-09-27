#include "Card.h"

#include <string>

Card::Card() {

}

Card::Card(int index, int value, std::string Color, std::string Type, std::string texturePath) {
	this->index = index;
	this->Value = value;
	this->Color = Color;
	this->Type = Type;
	this->texturePath = texturePath;
	cardShape.setSize(sf::Vector2f(this->width-5, this->height-5));
	cardShape.setOrigin(sf::Vector2f(1 / 2 * (this->width-5), 1 / 2 * (this->height - 5)));
	cardShape.setOutlineColor(Color::White);
	cardShape.setOutlineThickness(1);
};

void Card::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->cardShape, state);
};

void Card::setPosition(float X, float Y) {
	this->currentPositionX = X;
	this->currentPositionY = Y;
	this->cardShape.setPosition(X, Y);
};

std::pair<float, float> Card::getPosition() {
	return std::make_pair(this->currentPositionX, this->currentPositionY);
}

void Card::setTexture() {
	std::string path = "textures/cards/";
	TextureManager::loadTexture("card_" + std::to_string(this->getId()), path + this->texturePath);
	TextureManager::loadTexture("hiddenCard_" + std::to_string(this->getId()), path + "hidden.png");
};

RectangleShape Card::getShape() {
	return this->cardShape;
};

int Card::getId() {
	return this->index;
}

void Card::setHidden(const bool i) {
	std::string hiddenCard = "hiddenCard_";
	std::string card = "card_";

	this->hidden = i;
	if (i) {
		this->cardShape.setTexture(TextureManager::getTexture(hiddenCard + std::to_string(this->getId())));
	}
	else if (!i) {
		this->cardShape.setTexture(TextureManager::getTexture(card + std::to_string(this->getId())));
	}
}

bool Card::getHidden() {
	return this->hidden;
}

int Card::getValue() {
	return this->Value;
}

std::string Card::getColor() {
	return this->Color;
}

std::string Card::getType(){
	return this->Type;
}

void Card::setOutline(){
	this->cardShape.setOutlineThickness(10);
	this->cardShape.setOutlineColor(Color::Red);
}