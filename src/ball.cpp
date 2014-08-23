#include "../lib/ball.hpp"

#include <cmath>

Ball::Ball() {
	this->setRadius(5.0f);
	this->setFillColor(sf::Color::Green);
	this->setPosition(0.0f, 0.0f);
	direction_ = 0.0;
	speed_ = 640.0f / 2.0f - 2 * this->getRadius();
}



void Ball::setDirection(double direction) {
	direction_ = direction;
}



void Ball::center() {
	this->setPosition((640.0f - 2.0f * this->getRadius()) / 2.0f,
			(480.0f - 2.0f * this->getRadius()) / 2.0f);
}



void Ball::move(sf::Time elapsed) {
	// Move ball based on speed and direction.
	this->setPosition(
			this->getPosition().x +
			std::cos(direction_) * speed_ * elapsed.asSeconds(),
			this->getPosition().y +
			std::sin(-direction_) * speed_ * elapsed.asSeconds());
	// Bounce ball off walls.
	if (this->getPosition().y >= 480.0f - 2 * this->getRadius() ||
			this->getPosition().y <= 0.0f) {
		double vx = std::cos(direction_);
		double vy = -std::sin(direction_);
		direction_ = std::atan2(vy, vx);
		// Make sure the ball is not inside the wall.
		while (this->getPosition().y >= 480.0f - 2 * this->getRadius()) {
			this->setPosition(this->getPosition().x, this->getPosition().y - 1.0f);
		}
		while (this->getPosition().y <= 0.0f) {
			this->setPosition(this->getPosition().x, this->getPosition().y + 1.0f);
		}
	}
}



void Ball::increaseSpeed() {
	speed_ += 5.0f;
}
