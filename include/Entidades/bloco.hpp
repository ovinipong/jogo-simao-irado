#pragma once

#include "personagem.hpp"
#include "obstaculo.hpp"

using namespace entidades;

enum TipoBloco{
    CHAO,
    TETO,
    PAREDE,
    FUNDO
};

class Bloco : public entidades::Entidade
{
    private:
        int altura;
        int largura;

    public:
        Bloco(int _x=0, int _y=0, float larg=0.f, float alt=0.f, TipoBloco tipo=CHAO);
        ~Bloco();
        void executar();
        void colisaoBloco(Personagem* pP);
        void colisaoBloco(Obstaculo* pO);

        void salvar(std::ofstream& arquivo);
};