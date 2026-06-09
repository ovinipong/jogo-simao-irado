#include "bolo.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Bolo::Bolo(int _x, int _y):
Inimigo(_x, _y)
{
    setValido();
    velocidade_x = 0;
    estado = PARADO;
    tempo_parado = 2.0f;
    pulo_velocidade = 10.0f;
    num_vidas = 5;

    inicializarSprite("assets/bolo.png", 1, 64, 64, 8, 0, 0, sf::Vector2f(0.f, 0.f));

    colisao.setSize(sf::Vector2f(64.0f, 64.0f));
    colisao.setFillColor(sf::Color::Green);
}

Bolo::~Bolo()
{

}

void Bolo::executar()
{
    if (!valido) return;
    // Padrao para qualquer estado vai ser cair
    float gravidade_velocidade = 0.5;

    if (no_chao)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = velocidade_y + gravidade_velocidade;
    }

    // Estados
    switch(estado)
    {
        case(PARADO):
        {
            // Condicao para trocar
            if (timer_pular.getElapsedTime().asSeconds() >= tempo_parado)
            {
                estado = PULANDO;
                no_chao = false;
                velocidade_y = -pulo_velocidade;
                velocidade_x = ((rand() % 3) - 1) * 3;
            }
            break;
        }
        case(PULANDO):
        {
            if (no_chao)
            {
                timer_pular.restart();
                estado = PARADO;
                velocidade_x = 0;
            }
        }
    }

    no_chao = false;
    x = x + velocidade_x;
    y = y + velocidade_y;
    colisao.setPosition((float)x, (float)y);
}


const int Bolo :: get_vida() const
{
    return num_vidas; 
}

void Bolo :: inverterDirecao()
{

}