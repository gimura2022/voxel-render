#ifndef _game_hpp
#define _game_hpp

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

#include "camera.h"
#include "svo.hpp"

class Game {
public:
	static inline constexpr auto WINDOW_WIDTH  = 840;
	static inline constexpr auto WINDOW_HEIGHT = 480;

	static inline constexpr auto WINDOW_TITLE = "game";

	Game();

	void run();

private:
	void render();
	void update(double delta);

	bool running = true;
	sf::Vector2f mouse_pos;

	Camera camera = Camera(sf::Vector3f(0, 0, 0), sf::Vector3f(0, 0, -3));

	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::RenderWindow window;
	sf::Shader shader;
	sf::Clock delta_clock;
};

#endif
