#include "entidade.hpp"

using namespace std;
using namespace sf;

// Construtora
Entidade::Entidade(int _x, int _y)
{
    // Atribui as posicoes iniciais
    x = _x;
    y = _y;
}

Entidade::~Entidade()
{
    
}

RectangleShape Entidade::get_colisao()
{
    return(colisao);
}