#pragma once

#include "fase.hpp"

using namespace fases;

namespace fases{

class PrimeiraFase : public Fase
{
    private:
        int maxInimBolo;
        int maxAgua;

    public:
        PrimeiraFase(Jogador* pJog1=NULL, Jogador* pJog2=NULL, bool carregar_fase = false);
        ~PrimeiraFase();
        virtual void executar();
        void criarInimBolos();
        void criarObstAguas();
        virtual void criarInimigos();
        virtual void criarObstaculos();
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