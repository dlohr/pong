#ifndef INCLUDED_PADDLE_HPP
#define INCLUDED_PADDLE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Paddle : public sf::RectangleShape {
	public:
		Paddle();

		void setDirection(int direction);
		void centerLeft();
		void centerRight();
		void move(sf::Time elapsed);

	private:
		int direction_;
		int speed_;
};

#endif // INCLUDED_PADDLE_HPP
