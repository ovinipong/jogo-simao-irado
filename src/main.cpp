#include <SFML/Graphics.hpp>

#include "ente.hpp"
#include "jogador.hpp"
#include "inimigo_facil.hpp"
#include "bloco.hpp"
#include "gerenciador_colisoes.hpp"
#include "gerenciador_grafico.hpp"


using namespace entidades;

int main()
{
    //sf::RenderWindow window(sf::VideoMode(1280, 720), "Jogo foda");
    //window.setFramerateLimit(60);

    GerenciadorGrafico gg;
    GerenciadorColisoes gc;

    Ente::setGG(&gg);

    Jogador j1(100, 100);
    InimigoFacil i1(200, 50);
    Bloco b1(0, 380, 500, 100);
    Bloco b2(400, 280, 20, 80);
    gc.setJogador(&j1);
    gc.incluirInimigo(&i1);
    gc.incluirObstaculo(&b1);
    gc.incluirObstaculo(&b2);

    while (gg.window->isOpen()) 
    {
        sf::Event event;
        while (gg.window->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                gg.window->close();
            }
        }
        // Executa
        j1.executar();
        i1.executar();
        gc.executar();

        gg.window->clear();

        // Desenha
        j1.desenhar();
        i1.desenhar();
        b1.desenhar();
        b2.desenhar();
        
        gg.window->display();
    }

    return 0;
}
