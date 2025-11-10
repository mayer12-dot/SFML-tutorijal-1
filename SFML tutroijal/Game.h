#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>

class Game
{

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game objects
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
	void pollEvents();
	void update();
	void render();
};

