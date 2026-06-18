#include "plataforma.hpp"
#include <iostream>

using namespace std;

Plataforma::Plataforma(int _x, int _y, TipoPlataforma tipo):
Obstaculo(_x, _y), altura(0), pode_colidir (false)
{
    setValido();
    danoso=false;
    switch(tipo)
    {
        case PRATELEIRA:
        {
            setNoChao(true);
            id=7;

            altura = (rand() % 32) + 32;
            y -= altura;
            
            inicializarSprite("assets/prateleira.png", 1, 64, 64, 0, 0, 0, sf::Vector2f(0.f, 0.f));

            colisao.setSize(sf::Vector2f(frame_largura, 4));
            colisao.setFillColor(sf::Color::Red);
            colisao.setPosition(x, y);

            break;
        }
        case MESA:
        {
            setNoChao(false);
            id=8;

            inicializarSprite("assets/mesa.png", 1, 64, 64, 0, 0, 0, sf::Vector2f(0.f, -22.f));

            colisao.setSize(sf::Vector2f(frame_largura, 42));
            colisao.setFillColor(sf::Color::Red);
            colisao.setPosition(x, y);

            break;
        }
        case CRISTALEIRA:
        {
            setNoChao(false);
            id=9;
            
            inicializarSprite("assets/cristaleira.png", 1, 128, 128, 0, 0, 0, sf::Vector2f(0.f, 0.f));

            colisao.setSize(sf::Vector2f(frame_largura, 128));
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
    if (no_chao)
        velocidade_y = 0.0f;
    else
        velocidade_y = aplicarGravidade(velocidade_y, dt);

    y += velocidade_y * dt;
    colisao.setPosition(x, y);
    //sprite.setPosition(x, y);
}

void Plataforma::obstaculizar(entidades::Jogador* pJog)
{
    if (pJog == nullptr) return;

    // Se apertar para descer
    if (pJog->getSegundo()==false)//primeiro jogador
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sf::Vector2f pos = pJog->getXY();
            pos.y += 2.0f;
            pJog->setNoChao(false);
            pJog->setXY(pos);
            
            return;
        }
    }
    else //segundo jogador
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            sf::Vector2f pos = pJog->getXY();
            pos.y += 2.0f;
            pJog->setNoChao(false);
            pJog->setXY(pos);
            
            return;
        }
    }
    
    
    sf::FloatRect jogador_colisao = pJog->getColisao().getGlobalBounds();
    sf::FloatRect bloco_colisao = this->getColisao().getGlobalBounds();

    float pe_jogador_atual = jogador_colisao.top + jogador_colisao.height;
    float pe_jogador_anterior = pe_jogador_atual - pJog->getVelocidadeY();

    bool pode_colidir = false;
    if (pe_jogador_anterior <= bloco_colisao.top + 10.0f)
    {
        pode_colidir = true;
    }

    sf::FloatRect interseccao;

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

void Plataforma :: salvar()
{
    
}