#pragma once

#include "personagem.hpp"

namespace entidades {

class Jogador : public Personagem
{
    protected:
        int pontos;
        int move_speed;
        int velocidade_padrao;
        int x_anterior;
        sf::Clock timer_status;
        float tempo_efeito;

    public:
        Jogador(int _x, int _y);
        ~Jogador();
        void executar();
        void reverterPosicao();
        void aplicarLentidao(int nova_velocidade, float duracao);
        void receberDano(int dano);
};


    enum class EstadoJogador {
        PARADO,
        CORRENDO,
        PULANDO
    };

}