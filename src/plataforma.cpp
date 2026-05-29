#include "plataforma.hpp"

Plataforma::Plataforma(int _x, int _y):
Obstaculo(_x, _y)
{
    altura = (rand() % 50) + 16;
    y -= altura;
    
    pFig = new Figura("assets/plataforma.png");
    pFig->frame_atual= 0;
    pFig->total_frames= 1;
    pFig->frame_largura= 96;
    pFig->frame_altura= 32;
    pFig->contador= 0;
    pFig->v_animacao= 0;

    pFig->sprite.setTextureRect(sf::IntRect(0, 0, pFig->frame_largura, pFig->frame_altura));
    pFig->offset = {0.f, 0.f};//ajustar sprite

    colisao.setSize(sf::Vector2f(pFig->frame_largura, pFig->frame_altura));
    colisao.setFillColor(sf::Color::Red);
    colisao.setPosition(x, y);
}

Plataforma::~Plataforma()
{
    
}

void Plataforma::executar()
{
    
}

void Plataforma::obstaculizar(entidades::Jogador* pJog)
{
    // pJog->setVelocidadeY(-10.f);
    // pJog->setNoChao(false);
}