#ifndef INCLUDED_BALL_HPP
#define INCLUDED_BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball : public sf::CircleShape {
	public:
		Ball();

		void setDirection(double direction);
		void center();
		void move(sf::Time elapsed);
		void increaseSpeed();
		
		double getDirection() { return direction_; }

	private:
		double direction_; // Radians
		float speed_;
};

#endif // INCLUDED_BALL_HPP
