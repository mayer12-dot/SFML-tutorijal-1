#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    std::cout << this->window;
   this->window->setFramerateLimit(144);
}
void Game::initEnemies()
{
	this->enemy.setPosition(400.f, 300.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(3.f);
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}



//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions
void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            /*case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                break;*/
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
            break;
        case sf::Event::Closed:
            this->window->close();
            break;
        default:
            break;
        }
    }



}

void Game::update() {
	this->pollEvents();
}

void Game::render()
{
    /*
    *   @return void
    *   -clear old objects
	*   -draw new objects
	*   -display frame in window
	*	Render Game Objects
    */

    this->window->clear();

    //Draw your game objects here
	this->window->draw(this->enemy);

    this->window->display();
}
