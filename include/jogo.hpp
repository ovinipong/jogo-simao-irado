#pragma once

#include "jogador.hpp"
#include "gerenciador_grafico.hpp"
#include "primeira_fase.hpp"
//#include "segunda_fase.hpp"
#include "menu.hpp"

using namespace entidades;

enum Estado
{
    MENU, PRIMEIRA_FASE
};

class Jogo
{
    private:
        PrimeiraFase* fase1;
        Jogador* pJog1;
        GerenciadorGrafico gg;
        Menu menu;
        Estado estado;

    public:
        Jogo();
        ~Jogo();
        void executar();
        void setEstado(Estado e);
};