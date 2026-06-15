#pragma once

#include "ente.hpp"
#include <string>
#include <map>

class Jogo; 

enum TelaMenu
{
    PRINCIPAL, PONTUACAO, SELECAO_FASE, SELECAO_JOGADORES
};

class Menu : public Ente
{
    private:
        Jogo* pJogo;
        TelaMenu tela;
        sf::Font fonte;
        std::string nome_jogador;
        std::multimap<int, std::string, std::greater<int>> ordem_ranking;
        int fase_escolhida;

    public:
        Menu(Jogo* pJ = NULL);
        ~Menu();
        void executar();
        const std::string &getNomeJogador() const {return(nome_jogador);}
        void carregar_ranking();
        void set_estado(TelaMenu e) {tela = e;}
};