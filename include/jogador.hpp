#pragma once

#include "personagem.hpp"

class Jogador : public Personagem
{
    protected:
        int pontos;
        int move_speed;
        sf::RectangleShape sprite;

    public:
        Jogador(int _x, int _y);
        ~Jogador();
        void executar();
        void desenhar(sf::RenderWindow &window);
};