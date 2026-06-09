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
        std::vector<Projetil*> projeteis_rato;
    
    public:
        SegundaFase(Jogador* pJog=NULL);
        ~SegundaFase();
        void executar();
        void criarProjeteisRatos();
        void ajustarProjeteisRatos();

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
};
}