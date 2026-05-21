#include "inimigo_dificil.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

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

    colisao.setPosition((float)x, (float)y);
}

const int InimigoDificil :: get_vida() const
{
    return vida;
}

void InimigoDificil :: inverterDirecao()
{
    move_speed = -move_speed;
}