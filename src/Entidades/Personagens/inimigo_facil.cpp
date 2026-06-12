#include "inimigo_facil.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

InimigoFacil :: InimigoFacil(int _x, int _y): Inimigo(_x, _y)
{
    setValido();
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
    if (!valido) return;
    
    x = x + move_speed;
    
    if (getNoChao()==true)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = aplicarGravidade(velocidade_y, dt);
    }

    setNoChao(false);
    
    y += velocidade_y * dt;
    colisao.setPosition((float)x, (float)y);
}

const int InimigoFacil :: get_vida() const
{
    return num_vidas;
}

void InimigoFacil :: inverterDirecao()
{
    move_speed = -move_speed;
}