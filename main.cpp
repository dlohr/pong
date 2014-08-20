#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Pong by Dillon Lohr");

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}

		window.clear();
		// window.draw();
		window.display();
	}

	return 0;
}
