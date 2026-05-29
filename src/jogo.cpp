#include "jogo.hpp"

Jogo :: Jogo() : pJog1 (NULL)
{
    pJog1 = new Jogador(400, 100);
}

Jogo :: ~Jogo()
{
    delete pJog1;
}

void Jogo :: executar()
{

}
