#include <memory>
#include <random>
#include <string>

#include <SFML/Graphics/Glsl.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Color.hpp>

#include "game.hpp"
#include "svo.hpp"
#include "utils.hpp"

Game::Game()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setPosition(sf::Vector2i(0, 0));

	if (!shader.loadFromFile("shader.frag", sf::Shader::Fragment))
		error("can't load fragment shader");

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(0, 255);

	const auto get_random_color = [&dist, &rng] () -> sf::Color {
		return sf::Color(dist(rng), dist(rng), dist(rng));
	};

	svo::Node tree = svo::Node({
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(get_random_color()),
		std::make_unique<svo::Node>(std::array {
			std::make_unique<svo::Node>(),
			std::make_unique<svo::Node>(get_random_color()),
			std::make_unique<svo::Node>(get_random_color()),
			std::make_unique<svo::Node>(get_random_color()),
			std::make_unique<svo::Node>(get_random_color()),
			std::make_unique<svo::Node>(get_random_color()),
			std::make_unique<svo::Node>(),
			std::make_unique<svo::Node>(),
		}),
	});

	tree.set_in_shader("u_groups", shader);
}


void Game::run()
{
	while (running) {
		running = running ? window.isOpen() : running;

		for (auto event = sf::Event(); window.pollEvent(event);) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				mouse_pos = window.mapPixelToCoords({ event.mouseMove.x,
						event.mouseMove.y });
				break;

			default: break;
			}
		}

		update(delta_clock.restart().asSeconds());
		render();
	}
}

void Game::render()
{
	shader.setUniform("u_resolution", sf::Glsl::Vec2(window.getSize()));
	shader.setUniform("u_camera_pos", sf::Glsl::Vec3(camera.get_pos()));
	shader.setUniform("u_camera_dir", sf::Glsl::Vec3(camera.get_dir()));
 
        window.clear();
        window.draw(rect, &shader);
        window.display();
}

void Game::update(double delta)
{
	camera.update(delta);
}
