#include "inimigo.hpp"

using namespace std;
using namespace sf;


Inimigo :: Inimigo (int _x, int _y):
Personagem(_x, _y) 
{
    move_speed = 3;

    sprite.setSize(sf::Vector2f(50.0f, 50.0f));
    sprite.setFillColor(sf::Color::Red);
}

Inimigo :: ~Inimigo()
{

}

void Inimigo::executar()
{
    x = x + move_speed;

    if (x > 350 || x < 0)
        move_speed = -move_speed;

    sprite.setPosition((float)x, (float)y);
}

void Inimigo::desenhar(sf::RenderWindow& window) 
{
    window.draw(sprite);
}
