#pragma once
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../head/constants.h"
#include "../head/resources.h"

class Object : public sf::Sprite
{
public:
    Object(){};
};

class Block : public Object
{
public:
    Block(int shape);
    std::vector<std::vector<int>> m_shape;
    int m_x, m_y;
};

class Matrix : public Object
{
public:
    Matrix();
    std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> m_board{0};
};

class ScoreScreen : public Object
{
public:
    ScoreScreen(Resources &);
    void display(sf::RenderWindow &, int);
    sf::Text m_score;
};

class NextScreen : public Object
{
public:
    NextScreen(Resources &);
    void display(sf::RenderWindow &);
    Block m_nextBlock;
};