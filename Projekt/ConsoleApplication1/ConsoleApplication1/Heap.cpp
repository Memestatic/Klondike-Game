#include "Stack.h"
#include "Heap.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

using namespace sf;

Heap::Heap() {

}

Heap::Heap(float RectangleX, float RectangleY, std::string stackType) : Stack(0, width, height, stackType) {
    Shape.setPosition(pos_X, pos_Y);
    Shape.setSize(sf::Vector2f(this->width, this->height));
    Shape.setFillColor(Color::Transparent);
    Shape.setOutlineColor(Color(169, 169, 169));
    Shape.setOutlineThickness(3);
    this->stackType = stackType;
}

void Heap::draw(RenderTarget& target, RenderStates state) const {
    target.draw(Shape, state);
}

std::string Heap::getStackType() {
    return this->stackType;
}


