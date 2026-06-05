#pragma once

#include "lista_entidades.hpp"
#include "gerenciador_colisoes.hpp"
#include "ente.hpp"
#include "inimigo_facil.hpp"
#include "plataforma.hpp"
#include "bloco.hpp"
#include "jogador.hpp"
#include "agua.hpp"
#include "bolo.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <random>

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
        std::ifstream arquivo;
        int minimo_ent;
        float mapa_largura;
        float mapa_altura;
        Jogador* pJogador;

    public:
        Fase(const std::string& caminhoMapa, Jogador* pJog);
        ~Fase();
        void executar();
    protected:
        void move_camera();

        void criarInimFaceis();
        void criarPlataformas();
        virtual void criarInimigos()=0;
        virtual void criarObstaculos()=0;
        virtual void criarCenario();

        virtual int getMaxInimFaceis()=0;
        virtual int getMaxInimBolo()=0;
        virtual int getMaxPlataformas()=0;
        virtual int getMaxAgua()=0;
};

}