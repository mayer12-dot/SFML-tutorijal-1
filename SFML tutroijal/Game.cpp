#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    std::cout << this->window;
   this->window->setFramerateLimit(60);
}
void Game::initFonts()
{
    if (this->font.loadFromFile("Fonts/Cookies Gingerbread.otf")) {
        std::cout<< "Font loaded successfully" << std::endl;
    }
    else {
        std::cout << "Error loading font" << std::endl;
    }
}
void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("Points: " + std::to_string(this->points) + '\n' + "Health: " + std::to_string(this->health));
	this->uiText.setPosition(10.f, 10.f);
}
void Game::initEnemies()
{
	this->enemy.setPosition(400.f, 300.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	//this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    /*this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(3.f);*/
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
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

//const bool Game::getEndGame() const
//{
//    return this->endGame;
//}


//Functions
void Game::spawnEnemy()
{
    /*
    * @return void
    * 
	* Spawns enemies and sets their type, color and position ramdomly
	* -Sets a random position
	* -Sets a random color
	* -Adds enemy to the vector
    */

    this->enemy.setPosition(
        static_cast<float>(std::rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//Randomize the enemy
	int type = std::rand() % 4;

    switch (type)
    {
    case 0:
		this->enemy.setFillColor(sf::Color::Magenta);
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        break;
    case 1:
		this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        break;
    case 2:
		this->enemy.setFillColor(sf::Color::Cyan);
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        break;
    case 3:
		this->enemy.setFillColor(sf::Color::Green);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
    default:
        this->enemy.setFillColor(sf::Color::Yellow);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
    }

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

void Game::updateText()
{
    /*std::stringstream ss;

	ss << "Points: " << this->points;

	this->uiText.setString(ss.str());*/ // this works too, but simpler and faster to do below

	this->uiText.setString("Points: " + std::to_string(this->points) + '\n' + "Health: " + std::to_string(this->health));
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

		this->enemies[i].move(0.f, 2.f);

        //Remove enemy if bottom of screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
			this->health--;
            this->updateText();
        }
    }


    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
			this->mouseHeld = true;
            bool deleted = false;
            for (int i = 0; i < this->enemies.size() && !deleted; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 6;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 3;
					else
						this->points += 1;

                    this->updateText();

				    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
		this->mouseHeld = false;
}

void Game::update() {

	this->pollEvents();

    if (!this->endGame) {
        //Update mouse position
        this->updateMousePositions();

        this->updateEnemies();
    }

	//End game condition
    if (this->health <= 0)
		this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& e : this->enemies) {
		target.draw(e);
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
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
