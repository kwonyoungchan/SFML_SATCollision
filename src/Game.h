#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"
#include <queue>

typedef struct ST_GameData
{
	CStateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
}GameData;

typedef std::shared_ptr<GameData>GameDataRef;

class CGame
{
public:
	CGame(int width, int height, std::string title,float fps = 60);
	~CGame() {}
	void SetFrameRate(float fps);
private:
	float dt = 0;
	sf::Clock _clock;

	GameDataRef _data = std::make_shared<GameData>();

	void Run();
};

