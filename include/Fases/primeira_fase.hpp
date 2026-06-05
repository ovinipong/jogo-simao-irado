#pragma once

#include "fase.hpp"

using namespace fases;

namespace fases{

class PrimeiraFase : public Fase
{
    private:
        //lembrar: na implementação min é 3
        int maxInimFaceis; 
        int maxInimBolo;
        int maxPlataformas;
        int maxAgua;

    public:
        PrimeiraFase(Jogador* pJog);
        ~PrimeiraFase();
        virtual void executar();
    protected:
        void criarInimBolo();
        void criarObstAgua();
        virtual void criarInimigos();
        virtual void criarObstaculos();
    public:
        int getMaxInimFaceis()
        {
            return maxInimFaceis;
        }
        int getMaxInimBolo()
        {
            return (maxInimBolo);
        }
        int getMaxPlataformas()
        {
            return maxPlataformas;
        }
        int getMaxAgua()
        {
            return maxAgua;
        }
};

}