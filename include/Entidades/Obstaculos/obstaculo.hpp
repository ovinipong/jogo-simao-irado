#pragma once

#include "entidade.hpp"
#include "jogador.hpp"

class Obstaculo : public entidades::Entidade
{
    protected:
        bool danoso;
        bool no_chao;
    public:
        Obstaculo(int _x=0, int _y=0);
        virtual ~Obstaculo();
        virtual void executar() = 0;
        virtual void obstaculizar(entidades::Jogador* pJog) = 0;
        void setNoChao() {no_chao = true;}
        bool getNoChao() {return no_chao;}
};