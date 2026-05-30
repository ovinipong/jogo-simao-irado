#include "fase.hpp"
#include <iostream>

using namespace fases;

Fase :: Fase()
{

}

Fase :: ~Fase()
{

}

void Fase :: criarInimFaceis()
{
    int n_faceis = getMaxInimFaceis();
    int qntd = rand() % n_faceis + 1;

    int x=10;
    int y=50;

    if (qntd<3)
        qntd=3;

    for (int i = 0; i < qntd; i++)
    {
        InimigoFacil* inim = new InimigoFacil(x, y);
        lista_ents.incluir(inim); 
        gc.incluirInimigo(inim);
        x+=50;
    }
}

void Fase :: criarPlataformas()
{
    int n_plataf = getMaxPlataformas();
    int qntd = rand() % n_plataf + 1;

    if (qntd<3)
        qntd=3;

    for (int i = 0; i < qntd; i++)
    {
        int x = (rand() % 545);//544 nao passa a tela
        int y = (rand() % 321);
        Plataforma* plat = new Plataforma(x, y, PRATELEIRA);
        lista_ents.incluir(plat); 
        gc.incluirObstaculo(plat);
    }
}

void Fase::executar()
{
    //std::cout << "1" << std::endl;
    pGG->executar();
    //std::cout << "2" << std::endl;
    lista_ents.percorrer();
    //std::cout << "3" << std::endl;
    gc.executar();
    //std::cout << "4" << std::endl;
    pGG->mostrar();
}
