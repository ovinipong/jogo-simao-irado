#pragma once

#include <SFML/Graphics.hpp>

class Entidade
{
    protected:
        int x, y;

    public:
        Entidade(int _x, int _y);
        virtual ~Entidade() = 0;
        virtual void executar() = 0;
        virtual void desenhar(sf::RenderWindow &window) = 0;
};