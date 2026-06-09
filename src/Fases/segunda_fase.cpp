#include "segunda_fase.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

SegundaFase :: SegundaFase(Jogador *pJog):
Fase("assets/mapas/mapa2.txt", pJog),
maxInimRato(5),
maxLustre(5)
{
    srand(time(nullptr));
    criarCenario("assets/fundo1.png");
    criarInimigos();
    criarObstaculos();
    lista_ents.incluir(pJog);
    gc.setJogador(pJog);
    criarProjeteisJogador();
    criarProjeteisRatos();
}

SegundaFase :: ~SegundaFase()
{
    lista_ents.limpar();
}


void SegundaFase :: criarInimRato()
{
    arquivo.clear();
    arquivo.seekg(0);

    std::vector<sf::Vector2i> posicoes;
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {   
            if (linha[x]=='R')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});

            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxInimRato();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

    if (qntd > (int)posicoes.size())
    {
        qntd = (int)posicoes.size();
    }


    for (int i=0; i<qntd; i++)
    {
        Rato* inim = new Rato(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(inim); 
        gc.incluirInimigo(inim);
        inim->setListaProjeteis(&projeteis_rato);
    }

}

void SegundaFase :: criarObstLustre()
{
    arquivo.clear();
    arquivo.seekg(0);

    std::vector<sf::Vector2i> posicoes;
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {   
            if (linha[x]=='L')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});
            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxLustre();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

    if (qntd > (int)posicoes.size())
    {
        qntd = (int)posicoes.size();
    }


    for (int i=0; i<qntd; i++)
    {
        Lustre* obstaculo = new Lustre(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(obstaculo); 
        gc.incluirObstaculo(obstaculo);
    }
}


void SegundaFase :: criarInimigos()
{
    criarInimFaceis();
    criarInimRato();
}

void SegundaFase :: criarObstaculos()
{
    criarPlataformas();
    criarObstLustre(); //Esta comentado porque eles nao existem
}

void SegundaFase :: executar()
{
    Fase::executar();
    move_camera();
    if (pJogador->getXY().x >= 2200)
        concluida = true;
}

void SegundaFase :: criarProjeteisRatos()
{
    for (int i = 0; i < 10; i++)
    {
        Projetil* proj = new Projetil(-100, -100, RATO);
        gc.incluirProjetil(proj);
        lista_ents.incluir(proj);
        projeteis_rato.push_back(proj);
    }
}