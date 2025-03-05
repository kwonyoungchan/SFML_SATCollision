#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::Vector2i position = static_cast<sf::Vector2i>(object.getPosition());
        sf::Vector2i size = static_cast<sf::Vector2i>(object.getGlobalBounds().size);
        sf::IntRect tempRect(position,size);
        if (tempRect.contains(sf::Mouse::getPosition(window)))
        {
            return true;
        }
    }
    return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
    return sf::Mouse::getPosition();
}
