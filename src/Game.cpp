#include "Game.h"
#include "SplashState.h"
#include <iostream>
CGame::CGame(int width, int height, std::string title, float fps)
{
	sf::Vector2u size(width, height);
	_data->window.create(sf::VideoMode(size), title, sf::Style::Close | sf::Style::Titlebar);
	_data->machine.AddState(StateRef(new CSplashState(this->_data)),false);
	SetFrameRate(fps);
	this->Run();
}

void CGame::SetFrameRate(float fps)
{
	try
	{
		if (fps <= 0)
		{
			throw 0;
		}
		dt = 1 / fps;
	}
	catch(int e)
	{
		std::cout << "Error : wrong fps input received." << std::endl;
	}
	
}

void CGame::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	

	float accumulator = 0.0f;
	while (this->_data->window.isOpen())
	{
		// 상태 확인 
		this->_data->machine.ProcessStateChanges();
		//std::cout << "current State Size is: " << this->_data->machine.GetCurrentStateAmount() << std::endl;
		// 진행 시간 체크 
		newTime = this->_clock.getElapsedTime().asSeconds();
		// fps 체크 
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);
			accumulator -= dt;
		}
		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}

}
