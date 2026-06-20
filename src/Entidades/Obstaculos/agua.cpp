#include "agua.hpp"
#include <iostream>

using namespace entidades;

Agua::Agua(int _x, int _y):
Obstaculo(_x, _y)
{
    danoso=false;
    id = 10;
    setValido();
    setNoChao(false);
    reducao_velocidade = 1;
    float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    tempo = 2.0f + (chance * 3.0f);

    inicializarSprite("assets/agua.png", 2, 64, 64, 8, 0, 1, sf::Vector2f(0.f, -52.f));

    colisao.setSize(sf::Vector2f(frame_largura, 6));
    colisao.setFillColor(sf::Color::Red);
    colisao.setPosition(x, y);
}

Agua::~Agua()
{

}

void Agua::executar()
{
    if (getNoChao()==true)
        velocidade_y = 0.0f;
    else
        velocidade_y = aplicarGravidade(velocidade_y, dt);

    y += velocidade_y * dt;
    colisao.setPosition(x, y);
}

void Agua::obstaculizar(Jogador* pJog)
{
    pJog->aplicarLentidao(reducao_velocidade, tempo);
}


void Agua :: salvar(std::ofstream& arquivo)
{
    arquivo << id << " " << x << " " << y << std::endl;
}