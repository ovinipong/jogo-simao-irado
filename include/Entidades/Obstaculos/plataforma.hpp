#pragma once

#include "obstaculo.hpp"
#include "jogador.hpp"

enum TipoPlataforma{
    PRATELEIRA,
    MESA,
    CRISTALEIRA
};

class Plataforma : public Obstaculo
{
    private:
        int altura;
        bool pode_colidir;

    public:
        Plataforma(int _x, int _y, TipoPlataforma tipo);
        ~Plataforma();
        void executar();
        void obstaculizar(entidades::Jogador* pJog);
};