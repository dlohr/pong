#include "../lib/paddle.hpp"

Paddle::Paddle() {
	this->setSize(sf::Vector2f(25.0f, 100.0f));
	this->setFillColor(sf::Color::Green);
	this->setPosition(0.0f, 0.0f);
	direction_ = 0;
	speed_ = 480.0f - this->getSize().y;
}



void Paddle::setDirection(int direction) {
	direction_ = direction;
}



void Paddle::centerLeft() {
	this->setPosition(0.0f,
		(480.0f - this->getSize().y) / 2.0f);
}



void Paddle::centerRight() {
	this->setPosition(640.0f - this->getSize().x,
		(480.0f - this->getSize().y) / 2.0f);
}



void Paddle::move(sf::Time elapsed) {
	// TODO: Create global window size. [lohr] Thu 21 Aug 2014 10:22:01 PM CDT
	// Increase (or decrease) position based on speed and direction.
	this->setPosition(this->getPosition().x,
			this->getPosition().y + (speed_ * direction_) * elapsed.asSeconds());
	// Prevent the paddle from going offscreen.
	if (this->getPosition().y >= 480.0f - this->getSize().y) {
		this->setPosition(this->getPosition().x, 480.0f - this->getSize().y);
	} else if (this->getPosition().y <= 0.0f) {
		this->setPosition(this->getPosition().x, 0.0f);
	}
}
