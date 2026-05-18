#pragma once

#include "jogador.hpp"
#include "personagem.hpp"

class Inimigo : public Personagem 
{
    protected:
        int nivel_maldade;
        int move_speed;

    public:
        Inimigo(int _x, int _y);
        ~Inimigo();
        //void salvarDataBuffer();
        /*virtual*/ void executar();
        //virtual void danificar(Jogador* p) = 0;
        //virtual void salva() = 0;
        void desenhar (sf::RenderWindow &window);
};