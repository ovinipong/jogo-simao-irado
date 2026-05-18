#include "inimigo_facil.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

InimigoFacil :: InimigoFacil(int _x, int _y): Inimigo(_x, _y)
{
    dano=nivel_maldade*1;
}

InimigoFacil :: ~InimigoFacil()
{

}

void InimigoFacil :: executar()
{
    x = x + move_speed;

    if (x > 350 || x < 0)
        move_speed = -move_speed;

    sprite.setPosition((float)x, (float)y);
}

void InimigoFacil :: desenhar(sf::RenderWindow &window)
{
    window.draw(sprite);
}

const int InimigoFacil :: get_vida() const
{
    return vida;
}

sf::RectangleShape& InimigoFacil :: getSprite()
{
    return sprite;
}

void InimigoFacil :: inverterDirecao()
{
    move_speed = -move_speed;
}