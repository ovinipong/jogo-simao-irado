#pragma once

#include "obstaculo.hpp"
#include "jogador.hpp"

class Lustre : public Obstaculo
{
    private:
        bool caindo;
        int dano;
        float y_inicial;
    public:
        Lustre(int _x=0, int _y=0);
        ~Lustre();
        void executar();
        void obstaculizar(entidades::Jogador* pJog); 

        void salvar();
};