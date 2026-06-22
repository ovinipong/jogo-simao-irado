#pragma once

#include "jogador.hpp"
#include "personagem.hpp"

namespace entidades {

class Inimigo : public Personagem 
{
    protected:
        int nivel_maldade;
        int dano;

    public:
        Inimigo(int _x=0, int _y=0);
        ~Inimigo();
        virtual void executar()=0;
        virtual void danificar(Jogador* p) = 0;
        virtual void inverterDirecao() = 0;
        void setDano(){dano=nivel_maldade*2;};

        virtual void salvar(std::ofstream& arquivo) = 0;
};

}