#pragma once

#include "lista.hpp"
#include "entidade.hpp"

using namespace entidades;

namespace listas{

class ListaEntidades
{
    private:
        Lista<Entidade> LEs;
    public:
        ListaEntidades();
        ~ListaEntidades();
        void incluir(Entidade* pE);
        void percorrer();
        void percorrer_remover();
        void percorrer_desenhar();
        void remover(Entidade* pE);
        void limpar();
        void percorrerSalvar();
};

}