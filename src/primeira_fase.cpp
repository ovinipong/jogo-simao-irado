#include "primeira_fase.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

PrimeiraFase:: PrimeiraFase(Jogador* pJog) : Fase("assets/mapas/mapa1.txt"),
                                maxInimFaceis(5),
                                maxInimBolo(5),
                                maxPlataformas(5),
                                maxAgua(5)
{
    lista_ents.incluir(pJog);
    srand(time(nullptr));
    gc.setJogador(pJog);
    criarCenario();
    criarInimigos();
    criarObstaculos();

    pJogador = pJog;
}

PrimeiraFase :: ~PrimeiraFase()
{
       
}

void PrimeiraFase :: criarInimBolo()
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

void PrimeiraFase :: criarObstAgua()
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
    criarInimFaceis();
    criarInimBolo();
}

void PrimeiraFase :: criarObstaculos()
{
    criarPlataformas();
    criarObstAgua();
}

void PrimeiraFase :: executar()
{
    Fase::executar();
    move_camera();
}

// fase.cpp
void PrimeiraFase::move_camera()
{
    sf::Vector2f pos_camera = pJogador->getColisao().getPosition();
    // Ajuste para centralizar na figura
    pos_camera.x += 32;
    pos_camera.y += 64;

    float tamanho_da_tela = 320.f;
    float limite_esquerda = 0 + tamanho_da_tela;
    float limite_direita = 2240.f - tamanho_da_tela;
    float limite_baixo = 240.f;

    pos_camera.x = std::max(limite_esquerda, std::min(pos_camera.x, limite_direita));
    pos_camera.y = std::min(pos_camera.y, limite_baixo);

    pGG->centralizarCamera(pos_camera);
}