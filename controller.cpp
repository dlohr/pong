#include "controller.hpp"

Controller::Controller() {
	gameState_ = GameState::STATE_MENU;
	loadResources();
}



void Controller::beginGame() {
	// TODO: Initialize values
	gameState_ = GameState::STATE_RUNNING;
	gameClock_.restart();
}



void Controller::updateGame(sf::RenderWindow* window) {
	switch (gameState_) {
		case GameState::STATE_MENU:
		case GameState::STATE_GAMEOVER:
		case GameState::STATE_PAUSED:
			{
				sf::Text text;
				text.setFont(font_);
				if (gameState_ == GameState::STATE_MENU) {
					text.setString("Press ENTER to play!");
					text.setColor(sf::Color::Green);
				} else if (gameState_ == GameState::STATE_GAMEOVER) {
					// TODO: Set text to "PLAYER 1 WINS" or "PLAYER 2 WINS".
					text.setString("GAME OVER\nPress ENTER to play again!");
					text.setColor(sf::Color::Red);
				} else if (gameState_ == GameState::STATE_PAUSED) {
					text.setString("Press ENTER to resume!");
					text.setColor(sf::Color::Yellow);
				}
				text.setStyle(sf::Text::Bold);
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f);
				text.setPosition(640.0f / 2.0f, 480.0f / 2.0f);
				window->draw(text);
				break;
			}
		case GameState::STATE_RUNNING:
			{
				sf::Time elapsed = gameClock_.restart();
				// TODO: Perform calculations
				// TODO: Check gameover conditions
				break;
			}
		default:
			break;
	}
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



bool Controller::loadResources() {
	return (font_.loadFromFile("times-new-roman.ttf"));
}
