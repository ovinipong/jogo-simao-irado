#pragma once

#include "entidade.hpp"
#include "jogador.hpp"
#include "inimigo.hpp"


class Obstaculo : public entidades::Entidade
{
    protected:
        bool danoso;
    public:
        Obstaculo(int _x=0, int _y=0);
        virtual ~Obstaculo();
        virtual void executar() = 0;
        virtual void obstaculizar(entidades::Jogador* pJog) = 0;
        void obstaculizar(entidades::Inimigo *pInim, sf::FloatRect *obst, sf::FloatRect *interseccao);

        virtual void salvar() = 0;
};