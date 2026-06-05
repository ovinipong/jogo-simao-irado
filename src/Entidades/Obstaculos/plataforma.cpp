#include "plataforma.hpp"
#include <iostream>

using namespace std;

Plataforma::Plataforma(int _x, int _y, TipoPlataforma tipo):
Obstaculo(_x, _y), altura(0), pode_colidir (false)
{
    switch(tipo)
    {
        case PRATELEIRA:
        {
            danoso=false;
            id=7;

            altura = (rand() % 64) + 32;
            y -= altura;
            
            inicializarSprite("assets/prateleira.png", 1, 64, 64, 0, 0, 0, sf::Vector2f(0.f, 0.f));

            colisao.setSize(sf::Vector2f(frame_largura, 4));
            colisao.setFillColor(sf::Color::Red);
            colisao.setPosition(x, y);

            break;
        }
        case MESA:
        {
            danoso=false;
            id=8;

            inicializarSprite("assets/mesa.png", 1, 64, 64, 0, 0, 0, sf::Vector2f(0.f, 0.f));

            colisao.setSize(sf::Vector2f(frame_largura, 42));
            colisao.setFillColor(sf::Color::Red);
            colisao.setPosition(x, y);

            break;
        }
        case CRISTALEIRA:
        {
            danoso=false;
            id=9;
            
            inicializarSprite("assets/cristaleira.png", 1, 128, 128, 0, 0, 0, sf::Vector2f(0.f, 0.f));

            colisao.setSize(sf::Vector2f(frame_largura, 4));
            colisao.setFillColor(sf::Color::Red);
            colisao.setPosition(x, y);

            break;    
        }

    }
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