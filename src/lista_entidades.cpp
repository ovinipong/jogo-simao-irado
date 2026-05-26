#include "lista_entidades.hpp"

using namespace listas;

ListaEntidades :: ListaEntidades()
{
    //construtora lista template
}

ListaEntidades :: ~ListaEntidades()
{
    //destrutora lista template
}

void ListaEntidades :: incluir(Entidade* pE)
{
    LEs.incluir(pE);  
}

void ListaEntidades :: percorrer()
{

}