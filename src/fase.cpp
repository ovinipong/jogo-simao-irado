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

void Fase :: criarAgua()
{
    int n_agua = getMaxAgua();
    int qntd = rand() % n_agua + 1;

    if (qntd<3)
        qntd=3;

    for (int i = 0; i < qntd; i++)
    {
        int x = (rand() % 545);//544 nao passa a tela
        int y = (rand() % 321);
        Agua* agua = new Agua(x, y);
        lista_ents.incluir(agua); 
        gc.incluirObstaculo(agua);
    }
}

void Fase::executar()
{
    pGG->executar();                    // Limpa tela
    lista_ents.percorrer();             // Percorre executando
    gc.executar();                      // Ajusta a colisao
    lista_ents.percorrer_desenhar();    // Desenha na posicao correta
    pGG->mostrar();                     // Da display na tela
}
