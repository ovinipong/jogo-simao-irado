#pragma once

#include "entidade.hpp"

class Bloco : public entidades::Entidade
{
    private:
        sf::Color cor;

    public:
        Bloco(int _x=0, int _y=0, float largura=0.f, float altura=0.f);
        ~Bloco();
        void executar();
        void obstaculizar(entidades::Entidade* pE);
};