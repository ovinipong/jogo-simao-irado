#include "rato.hpp"
#include <iostream>
#include <stdexcept>
#include <map>

using namespace entidades;

int Rato :: contador_instancias = 0;

Rato::Rato(int _x, int _y, Jogador *pJ):
Inimigo(_x, _y), Thread()
{
    num_vidas = 5;
    nivel_maldade=3;
    setDano();
    setNoChao(false);
    pListaProjeteis = NULL;
    id_instancia = contador_instancias++;

    id = 5;

    inicializarSprite("assets/rato.png", 1, 78, 96, 1, 0, 0, sf::Vector2f(8.f, 0.f));
    colisao.setSize(sf::Vector2f(60.0f, 96.0f));
    colisao.setFillColor(sf::Color::Green);
    pJogador = pJ;

    iniciarThread(); //inicia a thread do rato 
}

Rato::~Rato()
{
    pararThread();
}

void Rato::executar() //no executar da fase 
{
    lock();

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

    unlock();
}

void* Rato::executarThread() //ao executar cria a sensação que o rato decidiu atirar
{
    while (getExecutando())
    {
        lock();
        if (!getValido())
        {
            pararThread();
            return NULL; //esperado pelo tipo da função (void*)
        }
        if (timer_atirar.getElapsedTime().asSeconds() >= 2)
        {
            atirar();
        }
        unlock();

        struct timespec ts; //<time.h>
        ts.tv_sec = 0;
        ts.tv_nsec = 50000000;
        nanosleep(&ts, NULL); // 0,05s, evita o uso total da CPU sem necessidade definindo um tempo de checagem do timer
    }
    return NULL; //esperado pelo tipo da função (void*)
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
    lock();
    p->receberDano(dano);
    unlock();
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

void Rato :: salvar(std::ofstream& arquivo)
{
    lock();
    arquivo << id << " " << x << " " << y << " " << num_vidas << " " << id_instancia << std::endl;
    unlock();
}

void Rato :: inverterDirecao()
{

}