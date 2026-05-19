#pragma once

#include "personagem.hpp"

class Bloco;

class Jogador : public Personagem
{
    protected:
        int pontos;
        int move_speed;
        
        float velocidade_y;
        bool no_chao;


    public:
        Jogador(int _x, int _y);
        ~Jogador();
        void executar();
        void desenhar(sf::RenderWindow &window);
        bool aabb(sf::RectangleShape r);

        void colisao_bloco(Bloco *b);
};