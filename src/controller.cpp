#include "../lib/controller.hpp"

#include <cmath>
#include <random>

Controller::Controller(sf::RenderWindow* window, unsigned int seed) {
	window_ = window;
	generator_.seed(seed);
	gameState_ = GameState::STATE_MENU;
	loadResources();
}



void Controller::gameLoop() {
	while (window_->isOpen()) {
		sf::Event event;

		while (window_->pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window_->close();
					break;

				case sf::Event::LostFocus:
					if (gameState_ == GameState::STATE_RUNNING) {
						// Pause the game on focus loss.
						pauseGame();
					}
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Return) {
						if (gameState_ == GameState::STATE_MENU) {
							// Start the game when ENTER is pressed on menu.
							beginGame();
						} else if (gameState_ == GameState::STATE_PAUSED) {
							// Resume the game when ENTER is pressed on pause.
							resumeGame();
						} else if (gameState_ == GameState::STATE_GAMEOVER) {
							// Restart the game when ENTER is pressed on gameover.
							beginGame();
						}
					}
					break;

				default:
					break;
			} // End switch (event.type)
		} // End while (window_->pollEvent(event))

		window_->clear(sf::Color::Black);

		switch (gameState_) {
			case GameState::STATE_MENU:
				drawState();
				// TODO: Play music. [lohr] Thu 21 Aug 2014 02:05:54 PM CDT
				break;

			case GameState::STATE_RUNNING:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					// W is pressed; move Player 1 up.
					paddle_[0].setDirection(-1);
				} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					// S is pressed; move Player 1 down.
					paddle_[0].setDirection(1);
				} else {
					// Neither is pressed; stop moving Player 1.
					paddle_[0].setDirection(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
					// I is pressed; move Player 2 up.
					paddle_[1].setDirection(-1);
				} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
					// K is pressed; move Player 2 down.
					paddle_[1].setDirection(1);
				} else {
					// Neither is pressed; stop moving Player 2.
					paddle_[1].setDirection(0);
				}

				updateGame();
				break;

			case GameState::STATE_GAMEOVER:
				drawState();
				// TODO: Play music. [lohr] Thu 21 Aug 2014 02:08:04 PM CDT
				break;

			case GameState::STATE_PAUSED:
				drawState();
				// TODO: Quiet music. [lohr] Thu 21 Aug 2014 02:08:28 PM CDT
				break;

			default:
				break;
		} // End switch (gameState_)

		window_->display();
	} // End while (window_->isOpen())
}



void Controller::drawState() {
	sf::Text text;
	text.setFont(font_);
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Bold);
	switch (gameState_) {
		case GameState::STATE_MENU:
			text.setString("Press ENTER to play!");
			text.setColor(sf::Color::Green);
			break;

		case GameState::STATE_GAMEOVER:
			// TODO: Add text "PLAYER x WINS" [lohr] Thu 21 Aug 2014 01:25:23 PM CDT
			text.setString("GAME OVER!\nPress ENTER to play again!");
			text.setColor(sf::Color::Red);
			break;

		case GameState::STATE_PAUSED:
			text.setString("Press ENTER to resume!");
			text.setColor(sf::Color::Yellow);
			break;

		default:
			break;
	}

	centerText(&text);
	window_->draw(text);
	gameClock_.restart();
}	



void Controller::beginGame() {
	// Center paddles on their respective sides.
	paddle_[0].centerLeft();
	paddle_[1].centerRight();
	// Center the ball in the middle of the screen.
	ball_.center();
	// Randomize the ball's initial trajectory.
	std::uniform_real_distribution<double> circle(0.0, 2 * M_PI);
	ball_.setDirection(circle(generator_));
	// Set gamestate to running.
	gameState_ = GameState::STATE_RUNNING;
	// Make sure the game clock starts counting when the game starts.
	gameClock_.restart();
	// Set wait time to 3 seconds.
	waitTime_ = sf::seconds(3.0f);
}



void Controller::updateGame() {
	sf::Time elapsed = gameClock_.restart();

	// Update ball.
	if (waitTime_.asSeconds() <= 0.0f) {
		ball_.move(elapsed);
		// Check gameover condition.
		if (ball_.getPosition().x <= 0.0f || ball_.getPosition().x >= 640.0f) {
			gameOver();
		}
	} else {
		waitTime_ -= elapsed;
	}
	window_->draw(ball_);

	// Update paddles.
	for (Paddle& p : paddle_) {
		p.move(elapsed);
		// Check for collisions.
		if (p.getGlobalBounds().intersects(ball_.getGlobalBounds())) {
			float k = 0.5f;
			float pv = p.getDirection();
			double vx = -std::cos(ball_.getDirection());
			double vy = std::sin(ball_.getDirection()) - k * pv;
			ball_.setDirection(std::atan2(vy, vx));
			// Make sure the ball is not inside the paddle.
			while (p.getGlobalBounds().intersects(ball_.getGlobalBounds())) {
				if (ball_.getPosition().x <= 640.0f / 2.0f) {
					ball_.setPosition(ball_.getPosition().x + 1.0f,
						ball_.getPosition().y);
				} else {
					ball_.setPosition(ball_.getPosition().x - 1.0f,
						ball_.getPosition().y);
				}
			}
		}
		window_->draw(p);
	}
}



void Controller::gameOver() {
	gameState_ = GameState::STATE_GAMEOVER;
}



void Controller::pauseGame() {
	gameState_ = GameState::STATE_PAUSED;
	waitTime_ = sf::seconds(3.0f);
}



void Controller::resumeGame() {
	gameState_ = GameState::STATE_RUNNING;
}



void Controller::centerText(sf::Text* text) {
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
	text->setPosition(640.0f / 2.0f, 480.0f / 2.0f);
}



bool Controller::loadResources() {
	return (font_.loadFromFile("../res/times-new-roman.ttf"));
}
