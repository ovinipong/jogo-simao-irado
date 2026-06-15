#include "primeira_fase.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

PrimeiraFase:: PrimeiraFase(Jogador* pJog1, Jogador* pJog2) : Fase("assets/mapas/mapa1.txt", pJog1, pJog2),
                                                              maxInimBolo(5),
                                                              maxAgua(5)
{
    srand(time(nullptr));
    criarCenario("assets/fundo1.png");
    criarInimigos();
    criarObstaculos();
    lista_ents.incluir(pJog1);
    gc.incluirJogadores(pJog1);
    if (pJog2->getValido()==true)//opção de 2 jogadores selecionada no menu
    {
        lista_ents.incluir(pJog2);
        gc.incluirJogadores(pJog2);
    }
    criarProjeteisJogador();
}

PrimeiraFase :: ~PrimeiraFase()
{
       lista_ents.limpar();
}

void PrimeiraFase :: criarInimBolos()
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
            if (linha[x]=='B')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});

            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxInimBolo();
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
        Bolo* inim = new Bolo(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(inim); 
        gc.incluirInimigo(inim);
    }
}

void PrimeiraFase :: criarObstAguas()
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
            if (linha[x]=='A')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});
            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxAgua();
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
        Agua* agua = new Agua(posicoes[i].x, posicoes[i].y +56);
        lista_ents.incluir(agua); 
        gc.incluirObstaculo(agua);
    }
}

void PrimeiraFase :: criarInimigos()
{
    criarInimBolinhos();
    criarInimBolos();
}

void PrimeiraFase :: criarObstaculos()
{
    criarPlataformas();
    criarObstAguas();
}

void PrimeiraFase :: executar()
{
    Fase::executar();
    move_camera();
    if ((pJogador1->getXY().x >= 2200) && (pJogador2->getXY().x >=2200))
        concluida = true;
}