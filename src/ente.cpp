#include "ente.hpp"

using namespace sf;

Ente::Ente()
{
    
}

Ente::~Ente()
{
	
}

// Retorna a colisao
const RectangleShape& Ente::getColisao() const
{
    return(colisao);
}

void Ente :: desenhar()
{
    pGG->desenharEnte(this);
}

GerenciadorGrafico* Ente :: pGG = NULL;

void Ente :: setGG(GerenciadorGrafico *pG)
{
    pGG = pG;
}

GerenciadorGrafico* Ente :: getGG()
{
    return pGG;
}


