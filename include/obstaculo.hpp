#pragma once

#include "entidade.hpp"
#include "jogador.hpp"

class Obstaculo : public entidades::Entidade
{
    protected:

    public:
        Obstaculo(int _x, int _y);
        virtual ~Obstaculo();
        virtual void executar() = 0;
        virtual void obstaculizar(entidades::Jogador* pJog) = 0;
};