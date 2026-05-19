#include <SFML/Graphics.hpp>

#include "jogador.hpp"
#include "inimigo.hpp"
#include "bloco.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 400), "Jogo nada boring, voce que é boring vinicius");
    window.setFramerateLimit(60);

    Jogador j1(200, 100);
    Inimigo i1(200,100);
    Bloco b1(50, 300);

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
            j1.desenhar(window);
            j1.colisao_bloco(&b1);
            j1.executar();

            if (j1.aabb(i1.get_colisao()))
            {
                sf::RectangleShape a;
                a.setPosition(10, 10);
                a.setSize(sf::Vector2f(20.0f, 20.0f));
                a.setFillColor(sf::Color::Red);
                window.draw(a);
            } 
            i1.executar();
            i1.desenhar(window);
        
            b1.desenhar(window);
        window.display();
    }

    return 0;
}
