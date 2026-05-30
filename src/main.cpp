#include <SFML/Graphics.hpp>
#include "ente.hpp"
#include "jogador.hpp"
#include "inimigo_facil.hpp"
#include "bloco.hpp"
#include "gerenciador_colisoes.hpp"
#include "gerenciador_grafico.hpp"
#include "plataforma.hpp"
#include "jogo.hpp"
#include "fase.hpp"
#include "primeira_fase.hpp"
#include "lista.hpp"
#include "lista_entidades.hpp"

#include <stdlib.h>
#include <time.h>

using namespace entidades;

int main()
{
    srand(time(NULL));

    //sf::RenderWindow window(sf::VideoMode(1280, 720), "Jogo foda");
    //window.setFramerateLimit(60);

    Jogo jogo;

    jogo.executar();
    //GerenciadorGrafico gg;
    //GerenciadorColisoes gc;

    //Ente::setGG(&gg);

    /*Jogador j1(400, 100);
    // InimigoFacil i1(0, 50);
    Bloco b1(0, 380, 64, 16);
    Bloco b2(64, 380, 64, 16);
    Bloco b3(128, 380, 64, 16);
    Bloco b4(192, 380, 64, 16);
    Bloco b5(256, 380, 64, 16);
    Bloco b6(400, 280, 64, 16);
    Bloco b7(320, 380, 64, 16);
    Bloco b8(384, 380, 64, 16);
    Bloco b9(448, 380, 64, 16);
    Plataforma p1(100, 320, PRATELEIRA);
    Plataforma p2 (0, 316, CRISTALEIRA);
    Plataforma p3 (150, 338, MESA);

    gc.setJogador(&j1);
    // gc.incluirInimigo(&i1);
    gc.incluirBloco(&b1);
    gc.incluirBloco(&b2);
    gc.incluirBloco(&b3);
    gc.incluirBloco(&b4);
    gc.incluirBloco(&b5);
    gc.incluirBloco(&b6);
    gc.incluirBloco(&b7);
    gc.incluirBloco(&b8);
    gc.incluirBloco(&b9);
    gc.incluirObstaculo(&p1);
    gc.incluirObstaculo(&p2);
    gc.incluirObstaculo(&p3);


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
        // i1.executar();
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
        p1.desenhar();
        p2.desenhar();
        p3.desenhar();
        j1.desenhar();

        // i1.desenhar();
        

        
        gg.window->display();
    }*/

    return 0;
}
