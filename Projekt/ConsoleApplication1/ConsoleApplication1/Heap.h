/*****************************************************************//**
 * \file   Heap.h
 * \brief  Heap of cards in top left corner (class)
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Stack.h"
using namespace sf;

class Heap : public Stack {
    /** Type of stack (stack / pile / heap). Implemented to differentiate different stacks in program. */
    std::string stackType;
public:
    /** Heap basic constructor */
    Heap();
    /** Heap constructor */
    Heap(float RectangleX, float RectangleY, std::string stackType);
    /** Heap destructor */
    ~Heap() = default;
    /** Heap drawing method (SFML) */
    void draw(RenderTarget& target, RenderStates state) const override;
    /** Getting stack type method */
    std::string getStackType();
};
