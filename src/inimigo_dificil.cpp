#include "inimigo_dificil.hpp"

using namespace std;
using namespace sf;

InimigoDificil :: InimigoDificil(int _x, int _y): Inimigo(_x, _y)
{
    dano=nivel_maldade*3;
}

InimigoDificil :: ~InimigoDificil()
{

}

void InimigoDificil :: executar()
{
    x = x + move_speed;

    if (x > 350 || x < 0)
        move_speed = -move_speed;

    sprite.setPosition((float)x, (float)y);
}

void InimigoDificil :: desenhar(sf::RenderWindow &window)
{
    window.draw(sprite);
}

const int InimigoDificil :: get_vida() const
{
    return vida;
}