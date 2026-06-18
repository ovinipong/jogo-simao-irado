#pragma once

#include "ente.hpp"
#include <string>
#include <map>

class Jogo; 

enum TelaMenu
{
    PRINCIPAL, PONTUACAO, SELECAO_FASE, SELECAO_JOGADORES, PAUSE
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

        sf::Texture btn_jogar;
        sf::Texture btn_ranking;
        sf::Texture btn_fase1;
        sf::Texture btn_fase2;
        sf::Texture btn_um_jogador;
        sf::Texture btn_dois_jogadores;
        sf::Texture btn_voltar;
        sf::Texture btn_continuar;
        sf::Texture btn_menu;

        sf::Sprite botao_jogar;
        sf::Sprite botao_ranking;
        sf::Sprite botao_ranking_voltar;
        sf::Sprite botao_fase1;
        sf::Sprite botao_fase2;
        sf::Sprite botao_fase_voltar;
        sf::Sprite botao_um_jogador;
        sf::Sprite botao_dois_jogadores;
        sf::Sprite botao_jogador_voltar;
        sf::Sprite botao_pause_menu;
        sf::Sprite botao_pause_continuar;

        sf::Texture textura_fundo_pause;
        sf::Sprite sprite_fundo_pause;
        sf::RectangleShape retangulo_escuro;

    public:
        Menu(Jogo* pJ = NULL);
        ~Menu();
        void executar();
        const std::string &getNomeJogador() const {return(nome_jogador);}
        void carregar_ranking();
        void set_estado(TelaMenu e) {tela = e;}
        void capturarFundo(sf::RenderWindow *window);
};