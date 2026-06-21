#include "bolo.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Bolo::Bolo(int _x, int _y):
Inimigo(_x, _y)
{
    setValido();

    nivel_maldade=2;
    setDano();
    velocidade_x = 0;
    estado = PARADO;
    tempo_parado = 2.0f;
    pulo_velocidade = 7.0f;
    num_vidas = 5;

    id = 4;

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

    if (getNoChao()==true)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = aplicarGravidade(velocidade_y, dt);
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
                setNoChao(false);
                velocidade_y = -pulo_velocidade;
                velocidade_x = ((rand() % 3) - 1) * 3;
            }
            break;
        }
        case(PULANDO):
        {
            if (getNoChao()==true)
            {
                timer_pular.restart();
                estado = PARADO;
                velocidade_x = 0;
            }
        }
    }

    setNoChao(false);
    x = x + velocidade_x;
    y += velocidade_y * dt;
    colisao.setPosition((float)x, (float)y);
}

//dano ao contato e pula de novo
void Bolo::danificar(Jogador* p)
{
    estado = PULANDO;
    setNoChao(false);
    velocidade_y = -pulo_velocidade;
    velocidade_x = ((rand() % 3) - 1) * 3;

    p->receberDano(dano);
}

void Bolo :: salvar(std::ofstream& arquivo)
{
    arquivo << id << " " << x << " " << y << " " << num_vidas << " " << velocidade_x << " " << velocidade_y << " " << estado << std::endl;
}

void Bolo :: inverterDirecao()
{

}