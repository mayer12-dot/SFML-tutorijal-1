#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    std::cout << this->window;
   this->window->setFramerateLimit(60);
}
void Game::initEnemies()
{
	this->enemy.setPosition(400.f, 300.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    /*this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(3.f);*/
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
void Game::spawnEnemy()
{
    /*
    * @return void
    * 
	* Spawns enemies and sets their color and position
	* -Sets a random position
	* -Sets a random color
	* -Adds enemy to the vector
    */

    this->enemy.setPosition(
        static_cast<float>(std::rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

    this->enemy.setFillColor(sf::Color::Cyan);

	//Spawn the enemy
    this->enemies.push_back(this->enemy);

}

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

void Game::updateMousePositions()
{
    /*
	* @return void
    * 
	* Update the mouse positions:
	*   Mouse position relative to window (Vector2i)
    */
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    /*
	* @return void
    * 
	* Update the enemy spawn timer and spawns enemies
	* when the total number of enemies is lower than the maximum
	* Moves enemies down the screen
	* Removes enemies at the bottom of the screen //TODO
    */

	//Update the enemy spawn timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
		    this->enemySpawnTimer = 0.f;
        }
        else
		    this->enemySpawnTimer += 1.f;
    }

	//Move and update enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
		bool deleted = false;

		this->enemies[i].move(0.f, 5.f);

        //Check if clicked upon
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                deleted = true;

				//Gain points
                this->points += 10.f;
            }

        }

        //Remove enemy if bottom of screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            deleted = true;
        }

        if (deleted) {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::update() {
	this->pollEvents();

    //Update mouse position
    this->updateMousePositions();

    this->updateEnemies();
}

void Game::renderEnemies()
{
    for (auto& e : this->enemies) {
		this->window->draw(e);
    }
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
    this->renderEnemies();

    this->window->display();
}
