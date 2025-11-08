#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
//#include <SFML/OpenGL.hpp>

using namespace sf;

int main() {
    
	RenderWindow window(VideoMode(640, 480), "Game 1", Style::Default);
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister generator (vrlo dobar i brz)

    // Uniformna raspodela u intervalu [1, 100]
    std::uniform_int_distribution<> distrib(1, 100);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                /*case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;*/
				case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
						window.close();
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
					break;
                default:
                    break;
			}
        }

        window.clear(sf::Color::White);

		//Draw your game objects here

		window.display();
    }


    return 0;
}