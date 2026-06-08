#include "personagem.hpp"

using namespace std;
using namespace entidades;

// Construtora
Personagem::Personagem(int _x, int _y):
Entidade(_x, _y)
{
    valido = true;
}

Personagem::~Personagem()
{
    
}

void Personagem :: operator--()
{
    num_vidas -= 1;
    if (num_vidas <= 0)
    {
        num_vidas=0;
        setInvalido();
        colisao.setPosition(-100, -100);
    }
}

