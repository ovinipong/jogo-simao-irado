#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y):
Obstaculo(_x, _y)
{
    sprite.setSize(sf::Vector2f(700.0f, 50.0f));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(_x, _y);
}

Bloco::~Bloco()
{

}

void Bloco::executar()
{

}

void Bloco::desenhar(RenderWindow &window)
{
    window.draw(sprite);
}