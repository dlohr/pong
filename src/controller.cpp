#include "../lib/controller.hpp"

Controller::Controller(sf::RenderWindow* window) {
	window_ = window;
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
				// TODO: Keyboard input. [lohr] Thu 21 Aug 2014 02:07:12 PM CDT
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

	centerText(&text, sf::Vector2f(640.0f, 480.0f));
	window_->draw(text);
}	



void Controller::beginGame() {
	// TODO: Initialize values
	gameState_ = GameState::STATE_RUNNING;
	gameClock_.restart();
}



void Controller::updateGame() {
	sf::Time elapsed = gameClock_.restart();
	// TODO: Perform calculations
	// TODO: Check gameover conditions
}



void Controller::gameOver() {
	gameState_ = GameState::STATE_GAMEOVER;
}



void Controller::pauseGame() {
	gameState_ = GameState::STATE_PAUSED;
}



void Controller::resumeGame() {
	gameState_ = GameState::STATE_RUNNING;
}



void Controller::centerText(sf::Text* text, sf::Vector2f windowSize) {
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
	text->setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}



bool Controller::loadResources() {
	return (font_.loadFromFile("../res/times-new-roman.ttf"));
}
