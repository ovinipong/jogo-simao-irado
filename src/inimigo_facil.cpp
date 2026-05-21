#include "inimigo_facil.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

InimigoFacil :: InimigoFacil(int _x, int _y): Inimigo(_x, _y)
{
    dano=nivel_maldade*1;
    velocidade_y = 0;
}

InimigoFacil :: ~InimigoFacil()
{

}

void InimigoFacil :: executar()
{
    x = x + move_speed;

    if (x > 350 || x < 0)
        move_speed = -move_speed;


    float gravidade_velocidade = 0.5;
    
    if (no_chao)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = velocidade_y + gravidade_velocidade;
    }

    no_chao = false;
    
    y = y + velocidade_y;    

    colisao.setPosition((float)x, (float)y);
}

const int InimigoFacil :: get_vida() const
{
    return vida;
}

void InimigoFacil :: inverterDirecao()
{
    move_speed = -move_speed;
}