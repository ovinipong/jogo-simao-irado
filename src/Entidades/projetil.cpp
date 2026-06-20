#include "projetil.hpp"
#include "rato.hpp"

#include <cmath>
#include <iostream>

using namespace entidades;

Projetil :: Projetil(int _x, int _y, TipoProjetil tp):
Entidade(_x, _y)
{
    setInativo();
    setValido();
    Jogador1 = false;
    dano = 1;
    velocidade_x = 20.f;
    velocidade_y = 0.0f;
    pRato = NULL;
    y_inicial_mhs = -100;
    tempo_mhs = 0.0f;

    projetil = tp;

    if (projetil == JOGADOR)
    {
        inicializarSprite("assets/coracao.png", 1, 16, 16, 0, 0, 0, sf::Vector2f(0.f, 0.f));
        colisao.setSize(sf::Vector2f(16.0f, 16.0f));
        colisao.setFillColor(sf::Color::Green);
    }
    else if (projetil == RATO)
    {
        inicializarSprite("assets/queijo.png", 1, 32, 32, 0, 0, 0, sf::Vector2f(0.f, 0.f));
        colisao.setSize(sf::Vector2f(32.0f, 32.0f));
        colisao.setFillColor(sf::Color::Green);
    }
}

Projetil :: Projetil():
Entidade(-100, -100)
{
    projetil = JOGADOR;
    
    dano = 1;
    velocidade_x = 8.f;
    velocidade_y = 0.0f;

    inicializarSprite("assets/coracao.png", 1, 16, 16, 0, 0, 0, sf::Vector2f(0.f, 0.f));
    colisao.setSize(sf::Vector2f(16.0f, 16.0f));
    colisao.setFillColor(sf::Color::Green);

}

Projetil :: ~Projetil()
{

}

void Projetil::executar()
{
    // Nem executa se não estiver ativo
    if (!ativo) return;

    if (projetil == JOGADOR)
    {
        x += velocidade_x;
        velocidade_y = aplicarGravidade(velocidade_y, dt);
        y += velocidade_y * dt;
    }
    else if (projetil == RATO && pRato != nullptr)
    {
        velocidade_y = aplicarGravidade (velocidade_y, dt);
        y += velocidade_y * dt;
        // Movimento em Y (MHS)
        // Formula do movimento harmonico simples
        // y(t) = yo + A * sen(w t)
        // y = centro do movimento + amplitude * sen(quao rapido oscila * tempo percorrido)
        tempo_mhs += dt * 0.5f;
        y = y_inicial_mhs + sin(tempo_mhs) * 25.0f;
        
        float dist_x = pRato->getColisao().getPosition().x - x;

        velocidade_x += (dist_x * 0.005f);
        velocidade_x *= 0.95f;
        x += velocidade_x;

        if (fabs(dist_x) < 40.0f && fabs(velocidade_x) < 5.0f)
        {
            setInativo();
        }
    }
    else if (projetil == RATO)
    {
        setInativo();
    }

    // Atualiza a caixa de colisão
    colisao.setPosition(x, y);
}

void Projetil :: disparar(sf::Vector2f pos_inicial, bool olhando_esquerda)
{
    setAtivo();
    x = pos_inicial.x;
    y = pos_inicial.y;
    colisao.setPosition(x, y);
    velocidade_y = 0.0f;

    tempo_mhs = 0.0f;
    y_inicial_mhs = pos_inicial.y;

    velocidade_x = 20.f;

    if (olhando_esquerda)
    {
        velocidade_x = -fabs(velocidade_x);
    }
    else
    {
        velocidade_x = fabs(velocidade_x);
    }
}

TipoProjetil Projetil :: getTipoProjetil()
{
    return(projetil);
}

void Projetil :: setInativo()
{
    ativo = false;
    setXY(sf::Vector2f(-100.f, -100.f)); 
    setDonoRato(NULL);
}

void Projetil :: setAtivo()
{
    ativo = true;
}

void Projetil :: salvar()
{

}