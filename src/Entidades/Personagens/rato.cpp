#include "rato.hpp"
#include <iostream>

using namespace entidades;

Rato::Rato(int _x, int _y):
Inimigo(_x, _y)
{
    num_vidas = 5;
    no_chao = false;

    inicializarSprite("assets/rato.png", 1, 78, 96, 1, 0, 0, sf::Vector2f(8.f, 0.f));
    colisao.setSize(sf::Vector2f(60.0f, 96.0f));
    colisao.setFillColor(sf::Color::Green);
}

Rato::~Rato()
{

}

void Rato::executar()
{
    float gravidade_velocidade = 0.5;

    if (no_chao)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = velocidade_y + gravidade_velocidade;
    }

    y = y + velocidade_y;
    colisao.setPosition((float)x, (float)y);
}


const int Rato::get_vida() const
{
    return num_vidas;
}

void Rato :: inverterDirecao()
{

}