#pragma once

#include "obstaculo.hpp"

class Bloco : public Obstaculo
{
    private:
        sf::Color cor;
    
    public:
        Bloco(int _x, int _y, float largura, float altura);
        ~Bloco();
        void executar();
};