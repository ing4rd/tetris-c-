#pragma once

#include "../head/object.h"

struct ActiveBlock
{
    ActiveBlock() : m_active{true}, m_block{rand() % NUMBER_OF_DIFFERENT_BLOCKS} {};
    bool m_active;
    Block m_block;
};

class State
{
public:
    State(){};
    virtual ~State(){};
    void changeState(int);

    virtual void logic(Resources &) = 0;
    virtual void update(Resources &, sf::RenderWindow &) = 0;
    virtual void input(Resources &) = 0;
    void wait(sf::Clock &);

    int m_changeState{};
};

class PlayingState : public State
{
public:
    PlayingState(Resources &r) : m_matrix{}, m_scoreScreen{r}, m_nextScreen{r} {};
    void input(Resources &) override;
    void logic(Resources &) override;
    void update(Resources &, sf::RenderWindow &) override;

    void move(int direction);
    void scanBoard();
    void clearLine(int);

    ActiveBlock m_activeBlock;
    Matrix m_matrix;
    ScoreScreen m_scoreScreen;
    NextScreen m_nextScreen;
};

class GameoverState : public State
{
public:
    GameoverState(Resources &){};
    void input(Resources &) override;
    void logic(Resources &) override;
    void update(Resources &, sf::RenderWindow &) override;
};

class MenuState : public State
{
public:
    MenuState(Resources &) : m_matrix{} {};
    void input(Resources &) override;
    void logic(Resources &) override;
    void update(Resources &, sf::RenderWindow &) override;

    void move(int direction);
    void scanBoard();
    void clearLine(int);

    Matrix m_matrix;
};