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
        Plataforma(int _x=0, int _y=0, TipoPlataforma tipo=PRATELEIRA);
        ~Plataforma();
        void executar();
        void obstaculizar(entidades::Jogador* pJog);
};