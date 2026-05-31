#include "agua.hpp"
#include <iostream>

using namespace entidades;

Agua::Agua(int _x, int _y):
Obstaculo(_x, _y)
{
    reducao_velocidade = (rand() % 2) + 1;
    // Gera um float entre 0.0 e 0.1
    float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    tempo = 2.0f + (chance * 3.0f);

    pFig = new Figura("assets/agua.png");
    pFig->frame_atual= 0;
    pFig->total_frames= 2;
    pFig->frame_largura= 64;
    pFig->frame_altura= 64;
    pFig->contador= 0;
    pFig->v_animacao= 8;

    pFig->frame_inicial=0;
    pFig->frame_final=1;

    pFig->sprite.setTextureRect(sf::IntRect(0, 0, pFig->frame_largura, pFig->frame_altura));
    pFig->offset = {0.f, -58.f};//ajustar sprite

    colisao.setSize(sf::Vector2f(pFig->frame_largura, 6));
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