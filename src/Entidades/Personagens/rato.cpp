#include "rato.hpp"
#include <iostream>

using namespace entidades;

Rato::Rato(int _x, int _y, Jogador *pJ):
Inimigo(_x, _y)
{
    num_vidas = 5;
    nivel_maldade=3;
    setDano(nivel_maldade);
    setNoChao(false);

    inicializarSprite("assets/rato.png", 1, 78, 96, 1, 0, 0, sf::Vector2f(8.f, 0.f));
    colisao.setSize(sf::Vector2f(60.0f, 96.0f));
    colisao.setFillColor(sf::Color::Green);
    pJogador = pJ;
}

Rato::~Rato()
{

}

void Rato::executar()
{
    // ATIRAR PEW PEW
    if (timer_atirar.getElapsedTime().asSeconds() >= 2)
    {
        atirar();
    }

    if (getNoChao()==true)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = aplicarGravidade(velocidade_y, dt);
    }

    y += velocidade_y * dt;
    
    colisao.setPosition((float)x, (float)y);
}

void Rato :: atirar()
{
    if (!pListaProjeteis) return;

    colisao.setPosition(x, y);

    for (Projetil* proj : *pListaProjeteis)
    {
        if (!proj->getAtivo())
        {
            sf::Vector2f pos = colisao.getPosition();
            proj->disparar(pos, getOlhandoEsquerda());
            proj->setDonoRato(this);
            timer_atirar.restart();
            break;
        }
    }
}

//dano ao contato e atira de novo
void Rato:: danificar(Jogador* p)
{
    p->receberDano(dano);
    atirar();
}

bool Rato :: getOlhandoEsquerda()
{
    if (x < pJogador->getColisao().getPosition().x)
    {
        return(false);
    }
    else
    {
        return(true);
    }
}