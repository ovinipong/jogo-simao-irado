#pragma once

#include "personagem.hpp"

namespace entidades {

class Jogador : public Personagem
{
    protected:
        int pontos;
        int move_speed;
        int x_anterior;
    public:
        Jogador(int _x, int _y);
        ~Jogador();
        void executar();
        void reverterPosicao();
};


    enum class EstadoJogador {
        PARADO,
        CORRENDO,
        PULANDO
    };

}