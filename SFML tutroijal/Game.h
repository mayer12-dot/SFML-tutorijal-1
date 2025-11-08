#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>

class Game
{

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	void initVariables();
	void initWindow();

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

