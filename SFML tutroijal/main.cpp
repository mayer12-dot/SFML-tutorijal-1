#include "Game.h"
//#include <SFML/OpenGL.hpp>

using namespace sf;

int main() {

    //RenderWindow window(VideoMode(800, 600), "Game 1", Style::Titlebar | Style::Close);
    //std::random_device rd;
    //std::mt19937 gen(rd()); // Mersenne Twister generator (vrlo dobar i brz)

	Game game;

    // Uniformna raspodela u intervalu [1, 100]
    //std::uniform_int_distribution<> distrib(1, 100);

	//init random seed
	std::srand(static_cast<unsigned>(time(0)));


    while (game.running())
    {
        // update
        game.update();

        // render
        game.render();
    }

    return 0;
}