#pragma once

#include <ctime>
#include <iostream>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();

public:	
	// Constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	//const bool getEndGame() const; // like it better to see screan than close it

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateText();
	void updateMousePositions();
	void updateEnemies();

	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

