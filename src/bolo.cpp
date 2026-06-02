#include "bolo.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Bolo::Bolo(int _x, int _y):
Inimigo(_x, _y)
{
    velocidade_x = 0;
    estado = PARADO;
    tempo_parado = 2.0f;
    pulo_velocidade = 10.0f;

    Figura("assets/bolo.png");

    frame_atual= 0;
    total_frames= 1;   
    frame_largura=64;
    frame_altura=64;  
    contador= 0;
    v_animacao= 8;// troca de frame a cada 8 ticks

    //primeiro ta sendo definido aqui
    sprite.setTextureRect(sf::IntRect(0, 0, frame_largura, frame_altura));
    offset = {0.f, 0.f};//ajustar sprite

    colisao.setSize(sf::Vector2f(64.0f, 64.0f));
    colisao.setFillColor(sf::Color::Green);
}

Bolo::~Bolo()
{

}

void Bolo::executar()
{
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
    return vida; 
}

void Bolo :: inverterDirecao()
{

}