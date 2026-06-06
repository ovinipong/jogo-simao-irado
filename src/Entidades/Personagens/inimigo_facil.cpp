#include "inimigo_facil.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

InimigoFacil :: InimigoFacil(int _x, int _y): Inimigo(_x, _y)
{
    id =3;
    dano=nivel_maldade*1;
    velocidade_y = 0;
    num_vidas = 3;

    inicializarSprite("assets/inimigo.png", 2, 64, 64, 8, 0, 0, sf::Vector2f(0.f, 3.f));

    colisao.setSize(sf::Vector2f(50.0f, 50.0f));
    colisao.setFillColor(sf::Color::Red);
}

InimigoFacil :: ~InimigoFacil()
{

}

void InimigoFacil :: executar()
{
    if (!vivo) return;
    
    x = x + move_speed;

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