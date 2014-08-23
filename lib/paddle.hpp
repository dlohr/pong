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

		int getDirection() { return direction_; }
		float getSpeed() { return speed_; }

	private:
		int direction_;
		float speed_;
};

#endif // INCLUDED_PADDLE_HPP
