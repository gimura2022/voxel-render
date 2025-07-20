#include <memory>
#include <random>
#include <string>
#include <optional>

#include <SFML/Graphics/Glsl.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Color.hpp>

#include "game.hpp"
#include "logger.hpp"
#include "svo.hpp"
#include "utils.hpp"

static logger::Logger logg("game-logger");

Game::Game()
{
	logg.info() << "initializing game";

	logg.debug() << "creating window";
	window.create(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_TITLE);
	window.setPosition(sf::Vector2i(0, 0));

	logg.debug() << "compiling shaders";
	if (!shader.loadFromFile("shaders/shader.frag", sf::Shader::Type::Fragment))
		utils::error("can't load fragment shader");

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(0, 255);

	const auto get_random_color = [&dist, &rng] () -> sf::Color {
		return sf::Color(dist(rng), dist(rng), dist(rng));
	};

	logg.debug() << "setting up octotree";
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
	logg.info() << "running main loop";

	while (running) {
		running = running ? window.isOpen() : running;

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				logg.debug() << "window close event polled";
			}
		}

		update(delta_clock.restart().asSeconds());
		render();
	}

	logg.info() << "shutting down";
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
