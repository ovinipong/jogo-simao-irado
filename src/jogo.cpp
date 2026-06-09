#include "jogo.hpp"
#include <iostream>

Jogo :: Jogo() : pJog1 (NULL), menu(this), fase1(NULL), fase2(NULL)
{
    Ente::setGG(&gg);
    pJog1 = new Jogador(400, 100);
    //fase1 = new PrimeiraFase(pJog1);
    //fase2 = new SegundaFase(pJog1);
    estado = MENU;
}

Jogo :: ~Jogo()
{
    delete pJog1;
    delete fase1;
    delete fase2;
}

void Jogo :: executar()
{
    while (gg.janelaAberta())
    {
        switch(estado)
        {
            case(PRIMEIRA_FASE):
            {
                if (!fase1)
                {
                    pJog1->setXY(sf::Vector2f(400, 100));
                    fase1 = new PrimeiraFase(pJog1);
                }
                fase1->executar();
                if (fase1->getConcluida())
                {
                    delete fase1;
                    fase1 = NULL;
                    std::cout << "trocando pra fase 2" << std::endl;
                    estado = SEGUNDA_FASE;
                }
                if (!pJog1->getValido())
                {
                    std::cout << "jogador morreu, voltando ao menu" << std::endl;
                    delete fase1;
                    fase1 = NULL;
                    delete pJog1;
                    pJog1 = new Jogador(400, 100);
                    estado = MENU;
                }
                break;
            }
            case(SEGUNDA_FASE):
            {
                if (!fase2)
                {
                    pJog1->setXY(sf::Vector2f(400, 100));
                    fase2 = new SegundaFase(pJog1);
                }
                fase2->executar();
                if (fase2->getConcluida())
                {
                    delete fase2;
                    fase2 = NULL;
                    std::cout << "fase 2 concluída, retornando para o menu" << std::endl;
                    estado = MENU;
                }
                if (!pJog1->getValido())
                {
                    delete fase2;
                    fase2 = NULL;
                    delete pJog1;
                    pJog1 = new Jogador(400, 100);
                    estado = MENU;
                }
                break;
            }
            case(MENU):
            {
                gg.centralizarCamera(sf::Vector2f(512.f, 288.f));
                gg.executar();
                menu.desenhar();
                menu.executar();
                gg.mostrar();
                break;
            }
        }   
    }
}

void Jogo :: setEstado(Estado e)
{
    estado = e;
}