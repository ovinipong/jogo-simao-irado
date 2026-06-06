#include "jogo.hpp"
#include <iostream>

Jogo :: Jogo() : pJog1 (NULL), menu(this)
{
    Ente::setGG(&gg);
    pJog1 = new Jogador(400, 100);
    fase1 = new PrimeiraFase(pJog1);
    fase2 = new SegundaFase(pJog1);
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
                fase1->executar();
                //std::cout<<"onde o jogador morre p eu por isso lista_ents.remover(pJog);"<<std::endl;
                break;
            }
            case(SEGUNDA_FASE):
            {
                fase2->executar();
                break;
            }
            case(MENU):
            {
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