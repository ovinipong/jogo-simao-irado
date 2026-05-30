#pragma once

#include "jogador.hpp"
#include "gerenciador_grafico.hpp"
#include "primeira_fase.hpp"
//#include "segunda_fase.hpp"
//#include "menu.hpp"

using namespace entidades;

class Jogo
{
    private:
        PrimeiraFase* fase1;
        Jogador* pJog1;
        GerenciadorGrafico gg;
    public:
        Jogo();
        ~Jogo();
        void executar();
};