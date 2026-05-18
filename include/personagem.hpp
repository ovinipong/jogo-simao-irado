#pragma once

#include "entidade.hpp"

namespace entidades {

class Personagem : public Entidade
{
    protected:
        int num_vidas;
    public:
        Personagem(int _x, int _y);
        virtual ~Personagem() = 0;
        virtual void executar() = 0;
        virtual void desenhar(sf::RenderWindow &window) = 0;
        virtual sf::RectangleShape& getSprite()=0;
};

}