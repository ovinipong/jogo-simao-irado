#include "jogo.hpp"
#include <iostream>

Jogo :: Jogo() : pJog1 (NULL)
{
    Ente::setGG(&gg);
    pJog1 = new Jogador(400, 100);
    fase1 = new PrimeiraFase(pJog1);
}

Jogo :: ~Jogo()
{
    delete pJog1;
    delete fase1;
}

void Jogo :: executar()
{
    while (gg.window->isOpen())
    {
        fase1->executar();
        //std::cout<<"onde o jogador morre p eu por isso lista_ents.remover(pJog);"<<std::endl;
    }

}
