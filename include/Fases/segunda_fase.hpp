#pragma once

#include "fase.hpp"

using namespace fases;

namespace fases
{
class SegundaFase : public Fase
{
    private:
        int maxInimRato;
        int maxLustre;

    public:
        SegundaFase(Jogador* pJog);
        ~SegundaFase();
        void executar();

    protected:
        void criarInimRato();
        void criarObstLustre();
        virtual void criarInimigos();
        virtual void criarObstaculos();
    public:
        int getMaxInimRato()
        {
            return (maxInimRato);
        }
        int getMaxLustre()
        {
            return (maxLustre);
        }
        int getMaxInimBolo();
        int getMaxAgua();
};
}