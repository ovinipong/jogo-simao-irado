#include "fase.hpp"

using namespace fases;

Fase :: Fase()
{

}

Fase :: ~Fase()
{

}

void Fase :: executar()
{
    lista_ents.percorrer();
    //trata colisoes
    //executar do ggrafico
}

void Fase :: criarInimFaceis()
{
    int n_faceis = getMaxInimFaceis();
    //criar inimigos c rand
    //chamar incluir da classe ListaEntidades
}

void Fase :: criarPlataformas()
{
    int n_plataf = getMaxPlataformas();
    //criar c rand
    //incluir na lista
}