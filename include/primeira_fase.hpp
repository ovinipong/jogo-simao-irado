#pragma once

#include "fase.hpp"

using namespace fases;

namespace fases{

class PrimeiraFase : public Fase
{
    private:
        //lembrar: na implementação min é 3
        int maxInimFaceis; 
        int maxInimMedios;
        int maxPlataformas;
        int maxAgua;
        Jogador* pJogador;

    public:
        PrimeiraFase(Jogador* pJog);
        ~PrimeiraFase();
        virtual void executar();
        void move_camera();
    protected:
        void criarInimMedios();
        void criarObstMedios();
        virtual void criarInimigos();
        virtual void criarObstaculos();
        virtual void criarCenario();
    public:
        int getMaxInimFaceis()
        {
            return maxInimFaceis;
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