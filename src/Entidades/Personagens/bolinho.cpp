#include "bolinho.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Bolinho :: Bolinho(int _x, int _y): Inimigo(_x, _y)
{
    setValido();
    id =3;
    dano=nivel_maldade*1;
    velocidade_y = 0;
    num_vidas = 3;

    inicializarSprite("assets/bolinho.png", 4, 64, 64, 8, 0, 0, sf::Vector2f(0.f, 3.f));

    colisao.setSize(sf::Vector2f(26.0f, 35.0f));
    colisao.setFillColor(sf::Color::Red);
}

Bolinho :: ~Bolinho()
{

}

void Bolinho :: executar()
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

const int Bolinho :: get_vida() const
{
    return num_vidas;
}

void Bolinho :: inverterDirecao()
{
    move_speed = -move_speed;
}