#include "lista_entidades.hpp"
#include "gerenciador_colisoes.hpp"
#include "ente.hpp"

using namespace listas;
using namespace gerenciadores;

class PrimeiraFase;

namespace fases {

class Fase : public Ente
{
    protected:
        ListaEntidades lista_ents;
        GerenciadorColisoes gc;
    public:
        Fase();
        ~Fase();
        virtual void executar();
    protected:
        void criarInimFaceis();
        void criarPlataformas();
        virtual void criarInimigos()=0;
        virtual void criarObstaculos()=0;
        virtual void criarCenario()=0;
};

}