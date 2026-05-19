#include <SFML/Graphics.hpp>

#include "jogador.hpp"
#include "inimigo_facil.hpp"
#include "bloco.hpp"
#include "gerenciador_colisoes.hpp"


using namespace entidades;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Jogo foda");
    window.setFramerateLimit(60);

    GerenciadorColisoes gc;
    Jogador j1(100, 100);
    InimigoFacil i1(200, 50);
    Bloco b1(50, 300);
    Bloco b2(50, 150);

    gc.setJogador(&j1);
    gc.incluirInimigo(&i1);
    gc.incluirObstaculo(&b1);
    gc.incluirObstaculo(&b2);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }
        // Executa
        j1.executar();
        i1.executar();
        gc.executar();

        window.clear();

        // Desenha
        j1.desenhar(window);
        i1.desenhar(window);
        b1.desenhar(window);
        b2.desenhar(window);
        
        window.display();
    }

    return 0;
}
