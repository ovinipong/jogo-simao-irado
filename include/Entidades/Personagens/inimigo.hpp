#pragma once

#include "jogador.hpp"
#include "personagem.hpp"

namespace entidades {

class Inimigo : public Personagem 
{
    protected:
        int nivel_maldade;
        int move_speed;
        int dano;

    public:
        Inimigo(int _x=0, int _y=0);
        ~Inimigo();
        //void salvarDataBuffer();
        virtual void executar()=0;
        virtual void danificar(Jogador* p) = 0;
        void inverterDirecao();
        //virtual void salva() = 0;
        void setDano(){dano=nivel_maldade*2;};

        virtual void salvar() = 0;
};

}