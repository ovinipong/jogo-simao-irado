#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y, float largura, float altura):
Obstaculo(_x, _y)
{
    colisao.setSize(sf::Vector2f(largura, altura));
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
