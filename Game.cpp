//
// Created by alex on 4/12/16.
//

#include "Game.h"
#include "GameState.h"

constexpr unsigned int winWidth{800}, winHeight{600};

Game::Game(): m_window({winWidth, winHeight}, "Legend of the Swamp")
{
    m_window.setFramerateLimit(60);

    loadTextures();
    m_background.setTexture(m_texmgr.getRef("background"));
}

void Game::run() {
    sf::Clock clock;

    while(m_window.isOpen())
    {
        sf::Time elapsed{clock.restart()};
        float dt{elapsed.asSeconds()};

        if(peekState() == nullptr)
        {
            continue;
        }

        peekState()->handleInput();
        peekState()->update(dt);

        m_window.clear(sf::Color::Black);

        peekState()->draw(dt);

        m_window.display();
    }
}


void Game::pushState(std::unique_ptr<GameState> state)
{
    // http://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
    m_states.push(std::move(state));
}

void Game::popState()
{
    m_states.pop();
}

void Game::changeState(std::unique_ptr<GameState> state)
{
    if(!m_states.empty())
    {
        popState();
    }

    pushState(std::move(state));
}

GameState* Game::peekState()
{
    if(m_states.empty())
    {
        return nullptr;
    }

    return m_states.top().get();
}

void Game::loadTextures()
{
    m_texmgr.loadTexture("background", "media/background.png");
}