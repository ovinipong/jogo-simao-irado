#include "obstaculo.hpp"

using namespace std;

Obstaculo::Obstaculo(int _x, int _y):
Entidade(_x, _y)
{

}

Obstaculo::~Obstaculo()
{
    
}

void Obstaculo::obstaculizar(entidades::Inimigo *pInim, sf::FloatRect *obst, sf::FloatRect *interseccao)
{
    sf::Vector2f pos = pInim->getXY();
    sf::FloatRect inim_colisao = pInim->getColisao().getGlobalBounds();

    // Colisao vertical (eixo Y)
    if (interseccao->height < interseccao->width)
    {
        // Colisao por cima (entidade em cima do bloco)
        if (inim_colisao.top < obst->top)
        {
            pos.y -= interseccao->height;
            pInim->setVelocidadeY(0.0f);
            pInim->setNoChao(true);
        }
        // Colisao por baixo (entidade em baixo do bloco)
        else
        {
            pos.y += interseccao->height;
            pInim->setVelocidadeY(0.0f);
        }
    }
    // Colisao horizontal (eixo X)
    else
    {
        // Colisao pela esquerda (entidade a direita do bloco)
        if (inim_colisao.left < obst->left)
        {
            pos.x -= interseccao->width;
        }
        // Colisao pela direita (entidade a esquerda do bloco)
        else
        {
            pos.x += interseccao->width;
        }
    }

    // Aplica a nova posição e atualiza a caixa de colisão da entidade
    pInim->setXY(pos);
    
    pInim->inverterDirecao();
}