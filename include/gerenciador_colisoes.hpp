#include <list>
#include <vector>
#include <set>

#include "inimigo.hpp"
#include "jogador.hpp"
#include "entidade.hpp"
#include "obstaculo.hpp"
//#include 

using namespace std;
using namespace entidades;

class GerenciadorColisoes
{
    private:
        vector <Inimigo*> inimigos;
        list <Obstaculo*> obstaculos;
    //    set <Projetil*> projeteis;
        Jogador* pJog;
    private:
        const bool verificarColisao(Entidade *pe1, Entidade *pe2);
        void tratarColisoesJogObst();
        void tratarColisoesJogInim();
        void tratarColisoesJogProj();
    public:
        GerenciadorColisoes();
        ~GerenciadorColisoes();
        void incluirInimigo(Inimigo *pi);
        void setJogador(Jogador *pj);
        void incluirObstaculo(Obstaculo *po);
        void executar();
};