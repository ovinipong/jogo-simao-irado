#include "jogo.hpp"

Jogo :: Jogo() : pJog1 (NULL)
{
    pJog1 = new Jogador(400, 100);
    fase1 = new PrimeiraFase(pJog1);
    Ente::setGG(&gg);
}

Jogo :: ~Jogo()
{
    delete pJog1;
    delete fase1;
}

void Jogo :: executar()
{
    fase1->executar();
}
