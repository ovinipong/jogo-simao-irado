#include "bloco.hpp"

using namespace std;
using namespace sf;

Bloco::Bloco(int _x, int _y, float largura, float altura):
entidades::Entidade(_x, _y)
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

void Bloco::obstaculizar(entidades::Entidade* pE)
{
    if (pE == nullptr) return;

    // Pega as colisoes
    sf::FloatRect interseccao;
    sf::FloatRect jogador_colisao = pE->getColisao().getGlobalBounds();
    sf::FloatRect bloco_colisao = this->getColisao().getGlobalBounds();

    // Atribui a interseccao se houver colisão
    if (jogador_colisao.intersects(bloco_colisao, interseccao))
    {
        sf::Vector2f pos = pE->getXY();

        // Colisao vertical (eixo Y)
        if (interseccao.height < interseccao.width)
        {
            // Colisao por cima (jogador em cima do bloco)
            if (jogador_colisao.top < bloco_colisao.top)
            {
                pos.y -= interseccao.height;
                pE->setVelocidadeY(0.0f);
                pE->setNoChao(true);
            }
            // Colisao por baixo (jogador embaixo do bloco)
            else
            {
                pos.y += interseccao.height;
                pE->setVelocidadeY(0.0f);
            }
        }
        // Colisao horizontal (eixo X)
        else
        {
            // Colisao pela esquerda (jogador à esquerda do bloco)
            if (jogador_colisao.left < bloco_colisao.left)
            {
                pos.x -= interseccao.width;
            }
            // Colisao pela direita (jogador à direita do bloco)
            else
            {
                pos.x += interseccao.width;
            }
        }

        // Aplica a nova posição e atualiza a caixa de colisão do jogador
        pE->setXY(pos);
    }
}