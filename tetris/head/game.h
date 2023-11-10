#pragma once
#include <memory>

#include <SFML/Window.hpp>

#include "state.h"
#include "resources.h"
#include "constants.h"

class Game
{
public:
    Game() : m_resources{}, m_state{std::make_unique<MenuState>(m_resources)}, m_window{sf::VideoMode{WIDTH, HEIGHT}, "Tetris"} {}
    void changeGameState();
    void play();

private:
    Resources m_resources;
    std::unique_ptr<State> m_state;
    sf::RenderWindow m_window;
};