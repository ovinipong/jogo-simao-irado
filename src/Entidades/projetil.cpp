#include "projetil.hpp"

#include <cmath>

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

void Projetil :: executar()
{
    // Nem executa o executar se nao tiver ativo
    if (!ativo) return;

    // Se tiver ativo, por enquanto, so move para a direita
    x += velocidade_x;
    velocidade_y = aplicarGravidade(velocidade_y, dt);
    y += velocidade_y * dt;
    colisao.setPosition(x, y);

    // Se for longe, meio que reseta
    if (x < -100 || x > 3000)
    {
        Jogador1 = false;
        setInativo();
        velocidade_y=0.0f;
        x = -100;
        y = -100;
    }
    colisao.setPosition(x, y);
}

void Projetil :: salvar()
{

}

void Projetil :: disparar(sf::Vector2f pos_inicial, bool olhando_esquerda)
{
    setAtivo();
    x = pos_inicial.x;
    y = pos_inicial.y;
    colisao.setPosition(x, y);
    velocidade_y = 0.0f;

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