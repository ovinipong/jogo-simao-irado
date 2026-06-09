#pragma once

#include "obstaculo.hpp"
#include "jogador.hpp"

class Agua : public Obstaculo
{
    protected:
        int reducao_velocidade; 
        float tempo;    
        
    public:
        Agua(int _x=0, int _y=0);
        ~Agua();
        void executar();
        void obstaculizar(entidades::Jogador* pJog);
};