#pragma once

#include "entidade.hpp"

class Bloco : public entidades::Entidade
{
    private:
        sf::Color cor;
    
    public:
        Bloco(int _x, int _y, float largura, float altura);
        ~Bloco();
        void executar();
        void obstaculizar(entidades::Entidade* pE);
};