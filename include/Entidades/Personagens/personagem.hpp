#pragma once

#include "entidade.hpp"

namespace entidades {

class Personagem : public Entidade
{
    protected:
        int num_vidas;

    public:
        Personagem(int _x=0, int _y=0);
        virtual ~Personagem();
        virtual void executar() = 0;
        void operator--();
        void receberDano(int dano);
};

}