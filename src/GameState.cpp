#include <sstream>
#include "GameState.h"
#include "Definitions.h"
#include <iostream>

#include "PauseState.h"
#include "Utilities.h"

const float dt = 0.016667;
CGameState::CGameState(GameDataRef data)
{
	_data = data;
}

CGameState::~CGameState()
{
	if (_background != nullptr) delete _background;
	if (_pauseButton != nullptr) delete _pauseButton;
}

void CGameState::Init()
{
	this->_data->assets.LoadTexture("GameBackground",GAME_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);

	_background = new sf::Sprite(this->_data->assets.GetTexture("GameBackground"));
	_pauseButton = new sf::Sprite(this->_data->assets.GetTexture("Pause Button"));

	const sf::Vector2f pauseButtonPosition =
		sf::Vector2f(
			this->_data->window.getSize().x - (_pauseButton->getLocalBounds().size.x),
			_pauseButton->getPosition().y);
	_pauseButton->setPosition(pauseButtonPosition);
	
	InitCollider();

}


void CGameState::HandleInput()
{
	CBaseState::HandleInput();
}

void CGameState::Update(float dt)
{
	UpdateBox();
	CheckCollision();
}

void CGameState::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(*_background);
	this->_data->window.draw(*_pauseButton);

	for (auto& c : m_Colliders)
		this->_data->window.draw(*c);

	this->_data->window.draw(m_box);

	this->_data->window.display();


}

void CGameState::Pause()
{
}

void CGameState::Resume()
{
}

void CGameState::OnKeyboardPressed(const sf::Event::KeyPressed* pressedEvent)
{
}


void CGameState::OnKeboardReleased(const sf::Event::KeyReleased* releasedEvent)
{
}


void CGameState::OnMouseButtonPressed(const sf::Event::MouseButtonPressed* pressedEvent, const sf::Vector2f pressedPosition)
{
	if (pressedEvent->button == sf::Mouse::Button::Left)
	{
		sf::FloatRect puseButtonBound = this->_pauseButton->getGlobalBounds();

		if (puseButtonBound.contains(pressedPosition))
		{
			this->_data->machine.AddState(StateRef(new CPauseState(_data)), false);
		}
	}
}


void CGameState::OnMouseButtonReleased(const sf::Event::MouseButtonReleased* releasedEvent, const sf::Vector2f releasedPosition)
{
}

void CGameState::InitCollider()
{
	{
		m_box.Create(sf::Vector2f(20.0f, 20.0f));
		m_box.SetOrigin(sf::Vector2f(.0f, .0f));
		m_box.SetPosition(MousePos(this->_data->window));
	}

	{
		CircleCollider* c = new CircleCollider();

		c->Create(40.0f);

		c->SetPosition(sf::Vector2f(110.0f, 110.0f));

		m_Colliders.push_back(c);
	}

	{
		CircleCollider* c = new CircleCollider();

		c->Create(20.0f);

		c->SetPosition(sf::Vector2f(500.0f, 150.0f));

		m_Colliders.push_back(c);
	}

	{
		BoxCollider* c = new BoxCollider();

		c->Create(sf::Vector2f(100.0f, 100.0f));

		c->SetPosition(sf::Vector2f(650.0f, 330.0f));

		c->SetRotation(sf::degrees(45.0f));

		m_Colliders.push_back(c);
	}

	{
		BoxCollider* c = new BoxCollider();

		c->Create(sf::Vector2f(200.0f, 100.0f));

		c->SetPosition(sf::Vector2f(120.0f, 560.0f));

		c->SetRotation(sf::degrees(25.0f));

		m_Colliders.push_back(c);
	}

	{

		CustomCollider* c = new CustomCollider(3);

		c->GetVerticles(0) = sf::Vector2f(0.0f, 0.0f);
		c->GetVerticles(1) = sf::Vector2f(80.0f, 80.0f);
		c->GetVerticles(2) = sf::Vector2f(100.0f, 0.0f);

		c->SetPosition(sf::Vector2f(600, 100.0f));

		c->SetRotation(sf::degrees(15.0f));

		m_Colliders.push_back(c);
	}

	{

		CustomCollider* c = new CustomCollider(6);

		c->GetVerticles(0) = sf::Vector2f(50.0f, 0.0f);
		c->GetVerticles(1) = sf::Vector2f(100.0f, 0.0f);
		c->GetVerticles(2) = sf::Vector2f(130.0f, 30.0f);
		c->GetVerticles(3) = sf::Vector2f(80.0f, 60.0f);
		c->GetVerticles(4) = sf::Vector2f(40.0f, 60.0f);
		c->GetVerticles(5) = sf::Vector2f(0.0f, 25.0f);

		c->SetPosition(sf::Vector2f(450.0f, 450.0f));

		c->SetRotation(sf::degrees(15.0f));

		m_Colliders.push_back(c);
	}

	{

		CustomCollider* c = new CustomCollider(4);

		c->GetVerticles(0) = sf::Vector2f(0.0f, 0.0f);
		c->GetVerticles(1) = sf::Vector2f(200.0f, 200.0f);
		c->GetVerticles(2) = sf::Vector2f(200.0f, 0.0f);
		c->GetVerticles(3) = sf::Vector2f(0.0f, -200.0f);
		
		c->SetPosition(sf::Vector2f(950.0f, 600.0f));

		c->SetRotation(sf::degrees(75.0f));

		m_Colliders.push_back(c);
	}
}

void CGameState::CheckCollision()
{
	for (auto& c : m_Colliders) {
		sf::Vector2f MTV;
		Collision::Instance.SATCollision(m_box, *c, MTV);

		m_box.Move(MTV);
	}
}

void CGameState::UpdateBox()
{
	constexpr float smoothness = 16.0f;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		m_box.Rotate(sf::degrees(100.0f *dt));

	sf::Vector2f start = m_box.GetPosition();
	sf::Vector2f end = MousePos(this->_data->window);

	sf::Vector2f pos = Lerp(start, end, smoothness * dt);

	m_box.SetPosition(pos);
}



