#include "primeira_fase.hpp"

PrimeiraFase:: PrimeiraFase() :
                                maxInimFaceis(5),
                                maxInimMedios(5),
                                maxPlataformas(5),
                                maxObstMedios(5)
{
    srand(time(nullptr));
    criarInimigos();
    criarObstaculos();
    criarCenario();
}

PrimeiraFase :: ~PrimeiraFase()
{
    
}

void PrimeiraFase :: criarInimMedios()
{
    //criar c rand
    //incluir na lista
}

void PrimeiraFase :: criarObstMedios()
{
    //criar c rand
    //incluir na lista
}

void PrimeiraFase :: criarInimigos()
{
    criarInimFaceis();
    criarInimMedios();
}

void PrimeiraFase :: criarObstaculos()
{
    criarPlataformas();
    criarObstMedios();
}

void PrimeiraFase :: criarCenario()
{
    int x = 0;

    for (int i=0; i<9; i++)
    {
        Bloco* bloco = new Bloco(x, 380, 64, 16);
        lista_ents.incluir(bloco);
    }

    Bloco* b = new Bloco(400, 280, 64, 16);
    lista_ents.incluir(b);

}