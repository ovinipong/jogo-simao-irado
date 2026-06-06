#pragma once

#include "entidade.hpp"

enum TipoProjetil
{
    JOGADOR, RATO
};

class Projetil : public entidades::Entidade
{
    private:
        bool ativo;
        int dano;
        float velocidade_x;
        TipoProjetil projetil;

    public:
        Projetil(int _x, int _y, TipoProjetil tp);
        ~Projetil();
        void executar();
        void salvar();
        void setAtivo(bool a);
        bool getAtivo() const;
        void disparar(sf::Vector2f pos_inicial, bool olhando_esquerda);
        TipoProjetil getTipoProjetil();
};