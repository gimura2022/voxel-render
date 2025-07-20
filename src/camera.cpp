#include <SFML/Window/Keyboard.hpp>

#include "camera.hpp"

void Camera::update(double delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		pos.z -= SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		pos.z += SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		pos.x -= SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		pos.x += SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		pos.y += SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		pos.y -= SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		dir.x += ROT_SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		dir.x -= ROT_SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		dir.y += ROT_SPEED * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		dir.y -= ROT_SPEED * delta;
}
