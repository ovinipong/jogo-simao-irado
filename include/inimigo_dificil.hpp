#pragma once

#include "inimigo.hpp"

namespace entidades {

class InimigoDificil : public Inimigo
{
    private:
        int dano;
        bool atacar;
    public:
        InimigoDificil(int _x, int _y);
        ~InimigoDificil();
        void executar();//descomentar virtual
        //void danificar(Jogador* p); sem implementação
        //void salva()=0;
        void desenhar (sf::RenderWindow &window);
        const int get_vida() const;
        virtual sf::RectangleShape& getSprite();
        virtual void inverterDirecao();
};

}