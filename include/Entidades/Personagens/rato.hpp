#pragma once

#include "inimigo.hpp"
#include "projetil.hpp"

namespace entidades
{

class Rato : public Inimigo
{
    private:
        std::vector<Projetil*>* pListaProjeteis;
        sf::Clock timer_atirar;
        Jogador *pJogador;

    public:
        Rato(int _x=0, int _y=0, Jogador *pJ = NULL);
        ~Rato();
        void executar();
        void danificar(Jogador* p);
        void inverterDirecao();
        void setListaProjeteis(std::vector<Projetil*>* pLista) { pListaProjeteis = pLista; }
        void atirar();
        bool getOlhandoEsquerda();
        void zerarTimerAtirar() { timer_atirar.restart(); };
};

}