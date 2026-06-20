#include "inimigo.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Inimigo :: Inimigo (int _x, int _y):
Personagem(_x, _y), nivel_maldade(10)
{
    move_speed = 3;
}

Inimigo :: ~Inimigo()
{

}

void Inimigo :: inverterDirecao()
{
    move_speed = -move_speed;
}