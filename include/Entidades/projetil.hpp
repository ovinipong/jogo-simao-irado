#pragma once

#include "entidade.hpp"

class Projetil : public entidades::Entidade
{
    private:
        bool ativo;
        int dano;
        float velocidade_x;

    public:
        Projetil(int _x, int _y);
        ~Projetil();
        void executar();
        void salvar();
        void setAtivo(bool a);
        bool getAtivo() const;
        void disparar(sf::Vector2f pos_inicial, bool olhando_esquerda);
};