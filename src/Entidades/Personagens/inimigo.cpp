#include "inimigo.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Inimigo :: Inimigo (int _x, int _y):
Personagem(_x, _y), nivel_maldade(10)
{

}

Inimigo :: ~Inimigo()
{

}
