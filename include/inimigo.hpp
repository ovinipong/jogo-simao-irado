#pragma once

#include "jogador.hpp"
#include "personagem.hpp"

namespace entidades {

class Inimigo : public Personagem 
{
    protected:
        int vida;
        int nivel_maldade;
        int move_speed;
        float velocidade_y;
        bool no_chao;

    public:
        Inimigo(int _x, int _y);
        ~Inimigo();
        //void salvarDataBuffer();
        virtual void executar()=0;
        //virtual void danificar(Jogador* p) = 0;
        //virtual void salva() = 0;
        virtual const int get_vida() const =0;
        virtual void inverterDirecao() =0;
        void colidir_bloco(sf::FloatRect *bloco, sf::FloatRect *personagem, sf::FloatRect *interseccao);
};

}