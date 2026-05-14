#include <SFML/Graphics.hpp>

#include "jogador.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Jogo Boring");
    window.setFramerateLimit(60);

    Jogador j1(200, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        window.clear();
            j1.executar();
            j1.desenhar(window);
        window.display();
    }

    return 0;
}