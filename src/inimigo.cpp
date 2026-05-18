#include "inimigo.hpp"

using namespace std;
using namespace sf;


Inimigo :: Inimigo (int _x, int _y):
Personagem(_x, _y), nivel_maldade(10)
{
    move_speed = 3;

    sprite.setSize(sf::Vector2f(50.0f, 50.0f));
    sprite.setFillColor(sf::Color::Red);
}

Inimigo :: ~Inimigo()
{

}
