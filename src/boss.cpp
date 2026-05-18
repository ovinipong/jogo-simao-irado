#include "boss.hpp"

using namespace std;
using namespace sf;

Boss:: Boss(int _x, int _y) : 
Inimigo(_x,_y)
{
    dano_meelee=nivel_maldade*5;
    dano_ranged=nivel_maldade*2;
    //adicionar relação com fraqueza
}

Boss:: ~Boss()
{

}

void Boss:: executar()
{
    x = x + move_speed;

    if (x > 350 || x < 0)
        move_speed = -move_speed;

    sprite.setPosition((float)x, (float)y);
}

const int Boss:: get_vida() const 
{
    return vida;
}

const int Boss:: get_fraqueza() const
{
    return fraqueza;
}

void Boss:: set_fraqueza()
{
    fraqueza--;
}


