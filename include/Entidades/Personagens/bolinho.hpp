#pragma once

#include "inimigo.hpp"

namespace entidades {

class Bolinho : public Inimigo
{
    private:
        int dano;
        bool atacar;
        
    public:
        Bolinho(int _x=0, int _y=0);
        ~Bolinho();
        void executar();//descomentar virtual
        //void danificar(Jogador* p); sem implementação
        //void salva()=0;
        const int get_vida() const;
        virtual void inverterDirecao();
};

}