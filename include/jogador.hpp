#pragma once

#include "personagem.hpp"

namespace entidades {

class Jogador : public Personagem
{
    protected:
        int pontos;
        int move_speed;
        float velocidade_y;
        bool no_chao;
        int x_anterior;
    public:
        Jogador(int _x, int _y);
        ~Jogador();
        void executar();
        void desenhar(sf::RenderWindow &window);
        virtual sf::RectangleShape& getSprite();
        void reverterPosicao();
        void colidir_bloco(sf::FloatRect *bloco, sf::FloatRect *personagem, sf::FloatRect *interseccao);
};

}