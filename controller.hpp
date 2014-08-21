#ifndef INCLUDED_CONTROLLER_HPP
#define INCLUDED_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Controller {
	public:
		Controller();

		enum GameState {
			STATE_MENU,
			STATE_RUNNING,
			STATE_GAMEOVER,
			STATE_PAUSED
		};

		void beginGame();
		void updateGame(sf::RenderWindow* window);
		void gameOver();
		void pauseGame();
		void resumeGame();

		GameState getGameState() { return gameState_; }

	private:
		GameState gameState_;

		sf::Clock gameClock_;

		sf::Font font_;

		bool loadResources();
};

#endif // INCLUDED_CONTROLLER_HPP
