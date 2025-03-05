#include <sstream>
#include "MainMenuState.h"
#include "Definitions.h"
#include <iostream>

#include "GameState.h"

CMainMenuState::CMainMenuState(GameDataRef data)
{
	_data = data;
}

CMainMenuState::~CMainMenuState()
{
	if (_background != nullptr) delete _background;
	if (_playButton != nullptr) delete _playButton;
	if (_title != nullptr) delete _title;
}

void CMainMenuState::Init()
{
	this->_data->assets.LoadTexture("Background",
		MAIN_MENU_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Play Button",
		MAIN_MENU_PLAY_BUTTON);
	this->_data->assets.LoadTexture("Game Title",
		MAIN_MENU_TITLE_PATH);

	this->_background= new sf::Sprite(this->_data->assets.GetTexture("Background"));
	this->_playButton = new sf::Sprite(this->_data->assets.GetTexture("Play Button"));
	this->_title = new sf::Sprite(this->_data->assets.GetTexture("Game Title"));

	const sf::Vector2f  playButtonPosition = sf::Vector2f(
		(SCREEN_WIDTH / 2) - (this->_playButton->getGlobalBounds().size.x / 2), 
		(SCREEN_HEIGHT / 2) - (this->_playButton->getGlobalBounds().size.y / 2));

	const sf::Vector2f  titlePosition = sf::Vector2f(
		(SCREEN_WIDTH / 2) - (this->_title->getGlobalBounds().size.x / 2),
		(100.0f) - (this->_title->getGlobalBounds().size.y * 0.1f));

	this->_playButton->setPosition(playButtonPosition);
	this->_title->setPosition(titlePosition);
}


void CMainMenuState::HandleInput()
{
	CBaseState::HandleInput();
}

void CMainMenuState::Update(float dt)
{
}

void CMainMenuState::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(*_background);
	this->_data->window.draw(*_playButton);
	this->_data->window.draw(*_title);

	this->_data->window.display();


}

void CMainMenuState::Pause()
{
}

void CMainMenuState::Resume()
{
}

void CMainMenuState::OnKeyboardPressed(const sf::Event::KeyPressed* pressedEvent)
{
}


void CMainMenuState::OnKeboardReleased(const sf::Event::KeyReleased* releasedEvent)
{
}


void CMainMenuState::OnMouseButtonPressed(const sf::Event::MouseButtonPressed* pressedEvent, const sf::Vector2f pressedPosition)
{
	if (pressedEvent->button == sf::Mouse::Button::Left)
	{
		sf::FloatRect playButtonBound = this->_playButton->getGlobalBounds();

		if (playButtonBound.contains(pressedPosition))
		{
			this->_data->machine.AddState(StateRef(new CGameState(_data)), true);
		}

	}
}

void CMainMenuState::OnMouseButtonReleased(const sf::Event::MouseButtonReleased* releasedEvent, const sf::Vector2f releasedPosition)
{
}


