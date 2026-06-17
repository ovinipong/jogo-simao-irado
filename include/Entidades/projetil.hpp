#pragma once

#include "entidade.hpp"

namespace entidades{
class Rato;
}

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
        bool Jogador1;
        entidades::Rato *pRato;
        float tempo_mhs;
        float y_inicial_mhs;

    public:
        Projetil(int _x, int _y, TipoProjetil tp);
        Projetil();
        ~Projetil();
        void executar();
        void salvar();
        void disparar(sf::Vector2f pos_inicial, bool olhando_esquerda);
        void disparar();
        TipoProjetil getTipoProjetil();

        void setAtivo();
        void setInativo();
        bool getAtivo() {return ativo;};
        bool getProjJog1() {return Jogador1;};
        void setOrigemProj(bool projJog1) {Jogador1=projJog1;};

        void setDonoRato(entidades::Rato* pR) { pRato = pR; }
        entidades::Rato* getDonoRato() { return(pRato); }
};