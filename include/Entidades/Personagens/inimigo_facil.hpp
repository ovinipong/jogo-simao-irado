#pragma once

#include "inimigo.hpp"

namespace entidades {

class InimigoFacil : public Inimigo
{
    private:
        int dano;
        bool atacar;
        
    public:
        InimigoFacil(int _x=0, int _y=0);
        ~InimigoFacil();
        void executar();//descomentar virtual
        //void danificar(Jogador* p); sem implementação
        //void salva()=0;
        const int get_vida() const;
        virtual void inverterDirecao();
};

}