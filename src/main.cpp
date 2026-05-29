#include <SFML/Graphics.hpp>
#include "ente.hpp"
#include "jogador.hpp"
#include "inimigo_facil.hpp"
#include "bloco.hpp"
#include "gerenciador_colisoes.hpp"
#include "gerenciador_grafico.hpp"
#include "plataforma.hpp"

#include <stdlib.h>
#include <time.h>

using namespace entidades;

int main()
{
    srand(time(NULL));

    //sf::RenderWindow window(sf::VideoMode(1280, 720), "Jogo foda");
    //window.setFramerateLimit(60);

    GerenciadorGrafico gg;
    GerenciadorColisoes gc;

    Ente::setGG(&gg);

    Jogador j1(400, 100);
    InimigoFacil i1(0, 50);
    Bloco b1(0, 380, 64, 16);
    Bloco b2(64, 380, 64, 16);
    Bloco b3(128, 380, 64, 16);
    Bloco b4(192, 380, 64, 16);
    Bloco b5(256, 380, 64, 16);
    Bloco b6(400, 280, 64, 16);
    Bloco b7(320, 380, 64, 16);
    Bloco b8(384, 380, 64, 16);
    Bloco b9(448, 380, 64, 16);
    Plataforma p1(100, 320);

    gc.setJogador(&j1);
    gc.incluirInimigo(&i1);
    gc.incluirObstaculo(&b1);
    gc.incluirObstaculo(&b2);
    gc.incluirObstaculo(&b3);
    gc.incluirObstaculo(&b4);
    gc.incluirObstaculo(&b5);
    gc.incluirObstaculo(&b6);
    gc.incluirObstaculo(&b7);
    gc.incluirObstaculo(&b8);
    gc.incluirObstaculo(&b9);
    gc.incluirObstaculo(&p1);


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
        b1.desenhar();
        b2.desenhar();
        b3.desenhar();
        b4.desenhar();
        b5.desenhar();
        b6.desenhar();
        b7.desenhar();
        b8.desenhar();
        b9.desenhar();
        j1.desenhar();
        i1.desenhar();
        p1.desenhar();
        

        
        gg.window->display();
    }

    return 0;
}
