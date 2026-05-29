#pragma once

#include "obstaculo.hpp"
#include "jogador.hpp"

class Plataforma : public Obstaculo
{
    private:
        int altura;

    public:
        Plataforma(int _x, int _y);
        ~Plataforma();
        void executar();
        void obstaculizar(entidades::Jogador* pJog);
};