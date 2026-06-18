#pragma once

#include "jogador.hpp"
#include "gerenciador_grafico.hpp"
#include "primeira_fase.hpp"
#include "segunda_fase.hpp"
#include "menu.hpp"

using namespace entidades;

enum Estado
{
    MENU, PRIMEIRA_FASE, SEGUNDA_FASE, PAUSADO
};

class Jogo
{
    private:
        PrimeiraFase* fase1;
        SegundaFase* fase2;
        Jogador* pJog1;
        Jogador* pJog2;
        GerenciadorGrafico gg;
        Menu menu;
        Estado estado;
        Estado estado_anterior;
        bool dois_jogadores;

    public:
        Jogo();
        ~Jogo();
        void executar();
        void setEstado(Estado e);
        void setDoisJogadores(bool dois_jog) {dois_jogadores = dois_jog;}
        bool getDoisJogadores() const {return(dois_jogadores);}
        void reiniciarFase();
        void continuarFase() { estado = estado_anterior; };
};