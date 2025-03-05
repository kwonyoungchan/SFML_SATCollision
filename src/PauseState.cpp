#include "PauseState.h"
#include "Definitions.h"
#include <iostream>
#include "GameState.h"
#include "MainMenuState.h"

CPauseState::CPauseState(GameDataRef data)
{
	_data = data;
}

CPauseState::~CPauseState()
{
	if (_background != nullptr) delete _background;
	if (_resumeButton != nullptr) delete _resumeButton;
	if (_homeButton != nullptr) delete _resumeButton;
}

void CPauseState::Init()
{
	this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
	this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

	this->_background = new sf::Sprite(this->_data->assets.GetTexture("Pause Background"));
	this->_resumeButton	 = new sf::Sprite(this->_data->assets.GetTexture("Resume Button"));
	this->_homeButton = new sf::Sprite(this->_data->assets.GetTexture("Home Button"));

	const sf::Vector2f resumeButtonPosition= sf::Vector2f(
			(SCREEN_WIDTH/2) - (this->_resumeButton->getGlobalBounds().size.x / 2), 
			(SCREEN_HEIGHT /3) - (this->_resumeButton->getLocalBounds().size.y / 2));

	const sf::Vector2f homeButtonPosition= sf::Vector2f(
			(SCREEN_WIDTH/2) - (this->_homeButton->getGlobalBounds().size.x / 2),
			(SCREEN_HEIGHT / 3*2) - (this->_homeButton->getLocalBounds().size.y / 2));

	this->_resumeButton->setPosition(resumeButtonPosition);
	this->_homeButton->setPosition(homeButtonPosition);
}

void CPauseState::HandleInput()
{
	CBaseState::HandleInput();
}

void CPauseState::Update(float dt)
{
}

void CPauseState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(*_background);
	this->_data->window.draw(*_resumeButton);
	this->_data->window.draw(*_homeButton);

	this->_data->window.display();
}

void CPauseState::Pause()
{
}

void CPauseState::Resume()
{
}

void CPauseState::OnKeyboardPressed(const sf::Event::KeyPressed* pressedEvent)
{
}

void CPauseState::OnKeboardReleased(const sf::Event::KeyReleased* releasedEvent)
{
}

void CPauseState::OnMouseButtonPressed(const sf::Event::MouseButtonPressed* pressedEvent, const sf::Vector2f pressedPosition)
{
	if (pressedEvent->button == sf::Mouse::Button::Left)
	{

		sf::FloatRect resumeButtonBound = this->_resumeButton->getGlobalBounds();
		sf::FloatRect homeButtonBound = this->_homeButton->getGlobalBounds();

		if (resumeButtonBound.contains(pressedPosition))
		{
			this->_data->machine.RemoveState();
		}
		if (homeButtonBound.contains(pressedPosition))
		{
			this->_data->machine.RemoveState();
			this->_data->machine.AddState(StateRef(new CMainMenuState(_data)), true);
		}

	}
}

void CPauseState::OnMouseButtonReleased(const sf::Event::MouseButtonReleased* releasedEvent, const sf::Vector2f releasedPosition)
{
}
