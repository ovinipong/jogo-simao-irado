#pragma once

#include "inimigo.hpp"

namespace entidades {

class Boss : public Inimigo
{
    private:
        int dano_ranged;
        int dano_meelee;
        int fraqueza;
        bool atacar;//depende de distancia
    public:
        Boss(int _x, int _y);
        ~Boss();
        void executar();
        void desenhar(sf::RenderWindow &window)=0;
        const int get_vida() const;
        const int get_fraqueza() const;
        void set_fraqueza();
        virtual sf::RectangleShape& getSprite();
        virtual void inverterDirecao();
};

}