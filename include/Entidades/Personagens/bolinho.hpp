#pragma once

#include "inimigo.hpp"

namespace entidades {

class Bolinho : public Inimigo
{
    private:
        int reducao_velocidade; 
        float tempo;
        
    public:
        Bolinho(int _x=0, int _y=0);
        ~Bolinho();
        void executar();
        void danificar(Jogador* p); //sem implementação
        void salvar();
};

}