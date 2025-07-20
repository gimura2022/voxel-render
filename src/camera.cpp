#include <SFML/Window/Keyboard.hpp>

#include "camera.hpp"

void Camera::update(double delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		pos.z -= SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		pos.z += SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		pos.x -= SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		pos.x += SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		pos.y += SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		pos.y -= SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dir.x += ROT_SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dir.x -= ROT_SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		dir.y += ROT_SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dir.y -= ROT_SPEED * delta;
}
