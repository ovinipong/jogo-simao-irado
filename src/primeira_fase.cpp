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
    //chao e fundo
}