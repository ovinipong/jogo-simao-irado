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

    public:
        Rato(int _x=0, int _y=0);
        ~Rato();
        void executar();
        const int get_vida() const; 
        void inverterDirecao();
        void setListaProjeteis(std::vector<Projetil*>* pLista) { pListaProjeteis = pLista; }
        void atirar();
};

}