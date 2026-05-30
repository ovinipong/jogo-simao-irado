#include "plataforma.hpp"
#include <iostream>

using namespace std;

Plataforma::Plataforma(int _x, int _y):
Obstaculo(_x, _y)
{
    altura = (rand() % 64) + 32;
    y -= altura;
    pode_colidir = false;
    
    pFig = new Figura("assets/plataforma.png");
    pFig->frame_atual= 0;
    pFig->total_frames= 1;
    pFig->frame_largura= 96;
    pFig->frame_altura= 32;
    pFig->contador= 0;
    pFig->v_animacao= 0;

    pFig->sprite.setTextureRect(sf::IntRect(0, 0, pFig->frame_largura, pFig->frame_altura));
    pFig->offset = {0.f, 0.95f};//ajustar sprite

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
    if (pJog == nullptr) return;

    // Se apertar para descer
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sf::Vector2f pos = pJog->getXY();
        pos.y += 2.0f;
        pJog->setNoChao(false);
        pJog->setXY(pos);
        
        return;
    }
    
    // Pega a posicao anterior do jogador para ver se ele esta em cima da plataforma
    sf::Vector2f aux = pJog->getXY() + pJog->getColisao().getSize();
    float posicao_anterior = aux.y - pJog->getVelocidadeY();

    bool pode_colidir = false;
    if (posicao_anterior <= y + 1.0f)
    {
        pode_colidir = true;
    }

    // Pega as colisoes
    sf::FloatRect interseccao;
    sf::FloatRect jogador_colisao = pJog->getColisao().getGlobalBounds();
    sf::FloatRect bloco_colisao = this->getColisao().getGlobalBounds();

    // Verifica a colisao se o jogador estiver caindo e tiver permissão para colidir
    if (pJog->getVelocidadeY() >= 0.0f && pode_colidir)
    {
        if (jogador_colisao.intersects(bloco_colisao, interseccao))
        {
            sf::Vector2f pos = pJog->getXY();

            // Colisao vertical (eixo Y)
            if (interseccao.height < interseccao.width)
            {
                // Colisao por cima (jogador pousando na plataforma)
                if (jogador_colisao.top < bloco_colisao.top)
                {
                    pos.y -= interseccao.height;
                    pJog->setVelocidadeY(0.0f);
                    pJog->setNoChao(true);
                }
            }
            
            pJog->setXY(pos);
        }
    }
}