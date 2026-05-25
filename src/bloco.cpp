#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y, float largura, float altura):
Obstaculo(_x, _y)
{
    cor = sf::Color::White;
    colisao.setSize(sf::Vector2f(largura, altura));
    colisao.setFillColor(cor);
    colisao.setPosition(_x, _y);

    pFig = new Figura ("assets/obstaculo.png");
}

Bloco::~Bloco()
{

}

void Bloco::executar()
{

}
