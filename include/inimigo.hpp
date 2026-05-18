#pragma once

#include "jogador.hpp"
#include "personagem.hpp"

class Inimigo : public Personagem 
{
    protected:
        int vida;
        int nivel_maldade;
        int move_speed;
        sf::RectangleShape sprite;
    public:
        Inimigo(int _x, int _y);
        ~Inimigo();
        //void salvarDataBuffer();
        virtual void executar()=0;
        //virtual void danificar(Jogador* p) = 0;
        //virtual void salva() = 0;
        virtual void desenhar (sf::RenderWindow &window)=0;
        virtual const int get_vida() const =0;
    
};