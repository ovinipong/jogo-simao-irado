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
        FloatRect jogador_colisao = pJog->getSprite().getGlobalBounds();
        FloatRect bloco_colisao = (*it)->getSprite().getGlobalBounds();

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
    tratarColisoesJogObst();
}