#include "agua.hpp"
#include <iostream>

using namespace entidades;

Agua::Agua(int _x, int _y):
Obstaculo(_x, _y)
{
    danoso=false;
    id = 10;
    reducao_velocidade = (rand() % 2) + 1;
    // Gera um float entre 0.0 e 0.1
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
    
}

void Agua::obstaculizar(Jogador* pJog)
{
    pJog->aplicarLentidao(reducao_velocidade, tempo);
    std::cout << tempo << std::endl;
    std::cout << reducao_velocidade << std::endl;
}