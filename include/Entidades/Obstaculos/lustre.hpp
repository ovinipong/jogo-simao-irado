#pragma once

#include "obstaculo.hpp"
#include "jogador.hpp"

class Lustre : public Obstaculo
{
    private:
        bool caindo;
        int dano;
        sf::RectangleShape area_colisao;
    public:
        Lustre(int _x, int _y);
        ~Lustre();
        void executar();
        void obstaculizar(entidades::Jogador* pJog); 
};