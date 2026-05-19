#include "entidade.hpp"
#include "gerenciador_colisoes.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

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

RectangleShape &Entidade::getSprite()
{
    return(sprite);
}