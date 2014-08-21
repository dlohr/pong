#ifndef INCLUDED_CONTROLLER_HPP
#define INCLUDED_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Controller {
	public:
		Controller(sf::RenderWindow* window);
		
		void gameLoop();

	private:
		enum GameState {
			STATE_MENU,
			STATE_RUNNING,
			STATE_GAMEOVER,
			STATE_PAUSED
		};

		sf::RenderWindow* window_;
		GameState gameState_;
		sf::Clock gameClock_;
		sf::Font font_;

		void drawState();                                                           
    
		void beginGame();                                                           
		void updateGame();                                                          
		
		void gameOver();                                                            
		void pauseGame();                                                           
		void resumeGame();

		void centerText(sf::Text* text, sf::Vector2f windowSize);
		bool loadResources();
};

#endif // INCLUDED_CONTROLLER_HPP
