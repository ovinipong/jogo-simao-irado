#pragma once

#include <SFML/Graphics.hpp>

namespace entidades{

class Entidade
{
    protected:
        int x, y;
        sf::RectangleShape sprite;
    public:
        Entidade(int _x, int _y);
        virtual ~Entidade() = 0;
        virtual void executar() = 0;
        virtual void desenhar(sf::RenderWindow &window) = 0;
        virtual sf::RectangleShape& getSprite() = 0;
};

}