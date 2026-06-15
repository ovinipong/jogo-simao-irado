#pragma once

#include "fase.hpp"

using namespace fases;

namespace fases{

class PrimeiraFase : public Fase
{
    private:
        //lembrar: na implementação min é 3
        int maxInimBolo;
        int maxAgua;

    public:
        PrimeiraFase(Jogador* pJog1=NULL, Jogador* pJog2=NULL);
        ~PrimeiraFase();
        virtual void executar();
    protected:
        void criarInimBolos();
        void criarObstAguas();
        virtual void criarInimigos();
        virtual void criarObstaculos();
    public:
        int getMaxInimBolo()
        {
            return (maxInimBolo);
        }
        int getMaxAgua()
        {
            return maxAgua;
        }
};

}