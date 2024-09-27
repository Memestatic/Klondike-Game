/*****************************************************************//**
 * \file   Pile.h
 * \brief  Four (collecting) piles of cards at the top (class)
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include "Stack.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace sf;

class Pile : public Stack {
    /** Pile type variable (clubs/diamonds/hearts/spades */
    std::string Type;
    /** Type of stack (stack / pile / heap). Implemented to differentiate different stacks in program. */
    std::string stackType;
public:
    /** Pile basic constructor */
    Pile();
    /**
     * Pile construcor.
     * 
     * \param RectangleX Pile position (x)
     * \param RectangleY Pile position (y)
     * \param stackType Stack type 
     */
    Pile(float RectangleX, float RectangleY, std::string stackType);
    /** Pile drawing method (SFML) */
    void draw(RenderTarget& target, RenderStates state) const override;
    /**
     * Setting pile type method.
     * 
     * \param x Type that we're setting
     */
    void setType(std::string x);
    /** Getting pile type method */
    std::string getType();
    /** Getting stack type method */
    std::string getStackType();
};
