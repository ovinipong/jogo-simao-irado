#pragma once

#include "obstaculo.hpp"
#include "jogador.hpp"

class Lustre : public Obstaculo
{
    private:
        bool no_teto;
        int dano;
    public:
        Lustre(int _x, int _y);
        ~Lustre();
        void executar();
        void obstaculizar(entidades::Jogador* pJog); 
};