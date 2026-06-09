#pragma once

#include "ente.hpp"

class Jogo; 

enum TelaMenu
{
    PRINCIPAL, PONTUACAO, SELECAO_FASE
};

class Menu : public Ente
{
    private:
        Jogo* pJogo;
        TelaMenu tela;
        sf::Font fonte;
    
    public:
        Menu(Jogo* pJ = NULL);
        ~Menu();
        void executar();
};