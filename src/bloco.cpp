#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y):
Obstaculo(_x, _y)
{
    colisao.setSize(sf::Vector2f(700.0f, 50.0f));
    colisao.setFillColor(sf::Color::White);
    colisao.setPosition(_x, _y);

    pFig = new Figura ("assets/obstaculo.png");
}

Bloco::~Bloco()
{

}

void Bloco::executar()
{

}
