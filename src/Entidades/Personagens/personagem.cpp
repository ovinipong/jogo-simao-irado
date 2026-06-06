#include "personagem.hpp"

using namespace std;
using namespace entidades;

// Construtora
Personagem::Personagem(int _x, int _y):
Entidade(_x, _y)
{
    vivo = true;
}

Personagem::~Personagem()
{
    
}

void Personagem :: operator--()
{
    num_vidas -= 1;
    if (num_vidas <= 0)
    {
        vivo = false;
        colisao.setPosition(-100, -100);
    }
}

bool Personagem :: get_vivo()
{
    return(vivo);
}
