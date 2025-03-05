#include "SplashState.h"
#include "Definitions.h"
#include <sstream>
#include <iostream>

#include "MainMenuState.h"

CSplashState::CSplashState(GameDataRef data)
{
	_data = data;
}

CSplashState::~CSplashState()
{
	if (_background != nullptr)
	{
		delete _background;
	}
}

void CSplashState::Init()
{
	this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	_background = new sf::Sprite(this->_data->assets.GetTexture("Splash State Background"));
	
}

void CSplashState::HandleInput()
{
	CBaseState::HandleInput();
}

void CSplashState::Update(float dt)
{
	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		// Switch to the Main Menu
		this->_data->machine.AddState(StateRef(new CMainMenuState(_data)), true);
	}
}

void CSplashState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(*_background);
	this->_data->window.display();

}

void CSplashState::Pause()
{
}

void CSplashState::Resume()
{
}

void CSplashState::OnKeyboardPressed(const sf::Event::KeyPressed* pressedEvent)
{
	if (pressedEvent->scancode == sf::Keyboard::Scancode::Escape)
	{
		this->_data->window.close();
	}
}

void CSplashState::OnKeboardReleased(const sf::Event::KeyReleased* releasedEvent)
{
}

void CSplashState::OnMouseButtonPressed(const sf::Event::MouseButtonPressed* pressedEvent, const sf::Vector2f pressedPosition)
{
}

void CSplashState::OnMouseButtonReleased(const sf::Event::MouseButtonReleased* releasedEvent, const sf::Vector2f releasedPosition)
{
}
