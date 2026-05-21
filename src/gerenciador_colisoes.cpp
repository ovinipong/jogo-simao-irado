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

void GerenciadorColisoes :: tratarColisoesJogObst()
{
    std::list<Obstaculo*>::iterator it;
    for (it = obstaculos.begin(); it != obstaculos.end(); ++it)
    {
        FloatRect interseccao;
        FloatRect jogador_colisao = pJog->getColisao().getGlobalBounds();
        FloatRect bloco_colisao = (*it)->getColisao().getGlobalBounds();

        // Se estiver colidindo
        if (jogador_colisao.intersects(bloco_colisao, interseccao))
        {
            pJog->colidir_bloco(&bloco_colisao, &jogador_colisao, &interseccao);
        }
    }
}

void GerenciadorColisoes :: incluirInimigo (Inimigo *pi)
{
    inimigos.push_back(pi);
}

void GerenciadorColisoes :: setJogador(Jogador *pj)
{
    pJog=pj;
}

void GerenciadorColisoes :: incluirObstaculo(Obstaculo *po)
{
    obstaculos.push_back(po);
}

const bool GerenciadorColisoes :: verificarColisao (Entidade *pe1, Entidade *pe2)
{
    if (pe1->getColisao().getGlobalBounds().intersects(pe2->getColisao().getGlobalBounds()))
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


void GerenciadorColisoes :: tratarColisoesEnemObst()
{
    std::list<Obstaculo*>::iterator it1;
    std::vector<Inimigo *>::iterator it2;
    for (it1 = obstaculos.begin(); it1 != obstaculos.end(); ++it1)
    {
        for (it2 = inimigos.begin(); it2 != inimigos.end(); ++it2)
        {
            FloatRect interseccao;
            FloatRect inimigo_colisao = (*it2)->getColisao().getGlobalBounds();
            FloatRect bloco_colisao = (*it1)->getColisao().getGlobalBounds();

            // Se estiver colidindo
            if (inimigo_colisao.intersects(bloco_colisao, interseccao))
            {
                (*it2)->colidir_bloco(&bloco_colisao, &inimigo_colisao, &interseccao);
            }
        }
    }
}

void GerenciadorColisoes :: executar()
{
    tratarColisoesEnemObst();
    tratarColisoesJogInim();
    tratarColisoesJogObst();
}