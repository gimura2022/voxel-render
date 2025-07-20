#include "game.hpp"
#include "logger.hpp"

int main()
{
	logger::Logger::init("log.log");

	Game game;
	game.run();

	return 0;
}
