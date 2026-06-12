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
#include "projetil.hpp"
#include "lustre.hpp"
#include "rato.hpp"

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
        int maxInimFaceis;
        int maxPlataformas;
        float mapa_largura;
        float mapa_altura;
        Jogador* pJogador;
        std::vector<Projetil*> projeteis_jogador;
        bool concluida;
        sf::Clock clock;//para ajustes de gravidade;

    public:
        Fase(const std::string& caminhoMapa="", Jogador* pJog=NULL);
        ~Fase();
        void executar();
        bool getConcluida() { return concluida; }
    protected:
        void move_camera();

        void criarInimFaceis();
        void criarPlataformas();
        virtual void criarInimigos()=0;
        virtual void criarObstaculos()=0;
        virtual void criarCenario(const std::string& caminhoFundo);
        void criarProjeteisJogador();
        void ajustarProjeteisJogador();
};

}