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
    int qntd = rand() % n_faceis + 1;

    for (int i = 0; i < qntd; i++)
    {
        // InimigoFacil* inim = new InimigoFacil(/*como vamos definir o parametro?*/);
        // lista_ents.incluir(inim); 
    }
}

void Fase :: criarPlataformas()
{
    int n_plataf = getMaxPlataformas();
    int qntd = rand() % n_plataf + 1;

    for (int i = 0; i < qntd; i++)
    {
        // Plataforma* plat = new Plataforma(/*como vamos definir o parametro?*/);
        // lista_ents.incluir(plat); 
    }
}