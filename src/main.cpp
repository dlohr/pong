#include "../lib/controller.hpp"

int main() {	
	sf::RenderWindow window(sf::VideoMode(640, 480), "Pong by Dillon Lohr");

	Controller controller(&window);
	controller.gameLoop();

	return 0;
}
