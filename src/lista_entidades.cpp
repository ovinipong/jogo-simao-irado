#include "lista_entidades.hpp"

using namespace listas;

ListaEntidades :: ListaEntidades() : LEs()
{
    
}

ListaEntidades :: ~ListaEntidades()
{
    
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