#pragma once

#include <ctime>
#include <iostream>
#include <vector>

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

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	void initVariables();
	void initWindow();
	void initEnemies();

public:	
	// Constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();

	void update();

	void renderEnemies();
	void render();
};

