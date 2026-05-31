#pragma once

#include "lista_entidades.hpp"
#include "gerenciador_colisoes.hpp"
#include "ente.hpp"
#include "inimigo_facil.hpp"
#include "plataforma.hpp"
#include "bloco.hpp"
#include "jogador.hpp"
#include "agua.hpp"

#include <cstdlib>
#include <ctime>

using namespace entidades;
using namespace listas;
using namespace gerenciadores;

//class PrimeiraFase;

namespace fases {

class Fase : public Ente
{
    protected:
        ListaEntidades lista_ents;
        GerenciadorColisoes gc;

    public:
        Fase();
        ~Fase();
        void executar();
    protected:
        void criarInimFaceis();
        void criarPlataformas();
        void criarAgua();
        virtual void criarInimigos()=0;
        virtual void criarObstaculos()=0;
        virtual void criarCenario()=0;

        virtual int getMaxInimFaceis()=0;
        virtual int getMaxPlataformas()=0;
        virtual int getMaxAgua()=0;
};

}