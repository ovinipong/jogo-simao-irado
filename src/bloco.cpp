#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y, float largura, float altura):
Obstaculo(_x, _y)
{
    cor = sf::Color::White;
    colisao.setSize(sf::Vector2f(largura, altura));
    colisao.setFillColor(cor);
    colisao.setPosition(_x, _y);

    pFig = new Figura ("assets/chao.png");

    pFig->frame_atual= 0;
    pFig->total_frames= 1;   
    pFig->frame_largura=64;
    pFig->frame_altura=64;  
    pFig->contador= 0;
    pFig->v_animacao= 8;// troca de frame a cada 8 ticks

    //primeiro ta sendo definido aqui
    pFig->sprite.setTextureRect(sf::IntRect(0, 0, pFig->frame_largura, pFig->frame_altura));
    pFig->offset = {0.f, -48.f};//ajustar sprite

    pFig->frame_inicial=0;
    pFig->frame_final=0;
}

Bloco::~Bloco()
{

}

void Bloco::executar()
{

}

void Bloco::obstaculizar(entidades::Jogador* pJog)
{

}