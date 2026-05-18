#pragma once

#include "entidade.hpp"

class Obstaculo : public Entidade
{
    protected:

    public:
        Obstaculo(int _x, int _y);
        virtual ~Obstaculo();
        virtual void executar() = 0;
        virtual void desenhar(sf::RenderWindow &window) = 0;
};