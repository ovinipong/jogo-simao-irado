#pragma once

#include "inimigo.hpp"

class InimigoFacil : public Inimigo
{
    private:
        int dano;
        bool atacar;
    public:
        InimigoFacil(int _x, int _y);
        ~InimigoFacil();
        void executar();//descomentar virtual
        //void danificar(Jogador* p); sem implementação
        //void salva()=0;
        void desenhar (sf::RenderWindow &window);
        const int get_vida() const;
};