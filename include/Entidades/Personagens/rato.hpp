#pragma once

#include "inimigo.hpp"
#include "projetil.hpp"
#include "thread.hpp"

namespace entidades
{

class Rato : public Inimigo, public Thread
{
    private:
        std::vector<Projetil*>* pListaProjeteis;
        sf::Clock timer_atirar;
        Jogador *pJogador;
        int id_instancia;
        static int contador_instancias;

    public:
        Rato(int _x=0, int _y=0, Jogador *pJ = NULL);
        ~Rato();
        void executar(); //chamado pela thread principal 
        void* executarThread(); //chamado pela thread própria do rato 
        void danificar(Jogador* p);
        void inverterDirecao();
        void setListaProjeteis(std::vector<Projetil*>* pLista) { pListaProjeteis = pLista; }
        void atirar();
        bool getOlhandoEsquerda();
        void zerarTimerAtirar() { timer_atirar.restart(); };

        int getIdInstancia() { return(id_instancia); }
        void setIdInstancia(int _id) { id_instancia = _id; }

        void salvar(std::ofstream& arquivo);
};

}