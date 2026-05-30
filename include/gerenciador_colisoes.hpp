#pragma once

#include <list>
#include <vector>
#include <set>

#include "inimigo.hpp"
#include "jogador.hpp"
#include "entidade.hpp"
#include "obstaculo.hpp"
#include "bloco.hpp"

using namespace std;
using namespace entidades;

class GerenciadorColisoes
{
    private:
        vector <Inimigo*> inimigos;
        list <Obstaculo*> obstaculos;
        // set <Projetil*> projeteis;
        vector <Bloco*> blocos;
        Jogador* pJog;
    private:
        const bool verificarColisao(Entidade *pe1, Entidade *pe2);
        void tratarColisoesJogObst();
        void tratarColisoesJogInim();
        void tratarColisoesJogProj();
        void tratarColisoesInimObst();
        void tratarColisioesJogBloco();
        void tratarColisoesInimBloco();
        void arrumarColisoes(Entidade *pEnt, sf::FloatRect *bloco, sf::FloatRect *interseccao);

    public:
        GerenciadorColisoes();
        ~GerenciadorColisoes();
        void incluirInimigo(Inimigo *pi);
        void setJogador(Jogador *pj);
        void incluirObstaculo(Obstaculo *po);
        void incluirBloco(Bloco *pb);
        void executar();
};