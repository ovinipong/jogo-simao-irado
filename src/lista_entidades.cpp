#include "lista_entidades.hpp"

using namespace listas;

ListaEntidades :: ListaEntidades() : LEs()
{
    //construtora lista template
}

ListaEntidades :: ~ListaEntidades() :
{
    //destrutora lista template
}

void ListaEntidades :: incluir(Entidade* pE)
{
    LEs.incluir(pE);  
}

void ListaEntidades :: percorrer()
{
    auto aux = LEs.getPrimeiro();
    while (aux != NULL)
    {
        if (aux->pInfo != NULL)
        {
            aux->pInfo->executar();
        }
        aux = aux->getProx();
    }
}