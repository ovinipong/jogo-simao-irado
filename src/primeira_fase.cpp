#include "primeira_fase.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

PrimeiraFase:: PrimeiraFase(Jogador* pJog) : Fase("assets/mapas/mapa1.txt"),
                                maxInimFaceis(5),
                                maxInimMedios(5),
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
    //criarInimMedios();
}

void PrimeiraFase :: criarObstaculos()
{
    criarPlataformas();
    criarAgua();
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