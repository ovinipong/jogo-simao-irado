#include "gerenciador_colisoes.hpp"

using namespace std;
using namespace sf;

GerenciadorColisoes :: GerenciadorColisoes() : 
pJog(NULL)
{ 
    //tem set jogador depois pq nao sei como vai ficar quando tiverem 2 jogadores
}

GerenciadorColisoes :: ~GerenciadorColisoes()
{
    //desalocar vector
}

void GerenciadorColisoes :: incluirInimigo (Inimigo *pi)
{
    inimigos.push_back(pi);
}

void GerenciadorColisoes :: setJogador(Jogador *pj)
{
    pJog=pj;
}

const bool GerenciadorColisoes :: verificarColisao (Entidade *pe1, Entidade *pe2)
{
    if (pe1->getSprite().getGlobalBounds().intersects(pe2->getSprite().getGlobalBounds()))
        return true;
    else 
        return false;
}

void GerenciadorColisoes :: tratarColisoesJogInim()
{
    vector<Inimigo*>::iterator it;
    for (it=inimigos.begin(); it != inimigos.end(); it++)
    {
        if(verificarColisao(pJog, *it))
        {
            pJog->reverterPosicao();
            (*it)->inverterDirecao();
        }
    }
}


void GerenciadorColisoes :: executar()
{
    tratarColisoesJogInim();
}