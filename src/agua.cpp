#include "agua.hpp"
#include <iostream>

using namespace entidades;

Agua::Agua(int _x, int _y):
Obstaculo(_x, _y)
{
    id = 10;
    reducao_velocidade = (rand() % 2) + 1;
    // Gera um float entre 0.0 e 0.1
    float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    tempo = 2.0f + (chance * 3.0f);

    Figura("assets/agua.png");
    frame_atual= 0;
    total_frames= 2;
    frame_largura= 64;
    frame_altura= 64;
    contador= 0;
    v_animacao= 8;

    frame_inicial=0;
    frame_final=1;

    sprite.setTextureRect(sf::IntRect(0, 0, frame_largura, frame_altura));
    offset = {0.f, -58.f};//ajustar sprite

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