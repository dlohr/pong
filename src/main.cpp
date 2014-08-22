#include "../lib/controller.hpp"

#include <chrono>

int main() {
	using time = std::chrono::system_clock;
	
	sf::RenderWindow window(sf::VideoMode(640, 480), "Pong by Dillon Lohr");

	unsigned seed = time::now().time_since_epoch().count();

	Controller controller(&window, seed);
	controller.gameLoop();

	return 0;
}
