#include "ente.hpp"

using namespace sf;

Ente::Ente()
{

}

Ente::~Ente()
{

}

// Essa funcao e para desenhar, mas por enquanto desenha a colisao
void Ente::desenhar(RenderWindow &window)
{
    window.draw(colisao);
}

// Retorna a colisao
const RectangleShape& Ente::getColisao() const
{
    return(colisao);
}