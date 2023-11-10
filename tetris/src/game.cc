#include "../head/game.h"

void Game::changeGameState()
{
    std::unique_ptr<State> newStatePtr;
    auto newState{m_state->m_changeState};
    switch (newState)
    {
    case PLAYING:
        newStatePtr = std::make_unique<PlayingState>(m_resources);
        break;
    case GAMEOVER:
        newStatePtr = std::make_unique<GameoverState>(m_resources);
        break;
    case MENU:
        newStatePtr = std::make_unique<MenuState>(m_resources);
        break;
    default:
        break;
    }
    this->m_state.swap(newStatePtr);
}

void Game::play()
{
    while (m_window.isOpen())
    {
        sf::Clock clock;
        sf::Event event;
        while (m_window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                m_window.close();
        m_state->input(m_resources);
        m_state->logic(m_resources);
        m_state->update(m_resources, m_window);
        m_state->wait(clock);
        if (m_state->m_changeState != NOCHANGE)
            changeGameState();
    }
}
