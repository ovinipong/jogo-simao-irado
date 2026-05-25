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
            arrumarColisoes(pJog, &bloco_colisao, &interseccao);
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
                arrumarColisoes(*it2, &bloco_colisao, &interseccao);
            }
        }
    }
}

void GerenciadorColisoes::arrumarColisoes(Entidade *pEnt, sf::FloatRect *bloco, sf::FloatRect *interseccao)
{
    sf::Vector2f pos = pEnt->getXY();
    sf::FloatRect ent_colisao = pEnt->getColisao().getGlobalBounds();

    // Colisao vertical (eixo Y)
    if (interseccao->height < interseccao->width)
    {
        // Colisao por cima (entidade em cima do bloco)
        if (ent_colisao.top < bloco->top)
        {
            pos.y -= interseccao->height;
            pEnt->setVelocidadeY(0.0f);
            pEnt->setNoChao(true);
        }
        // Colisao por baixo (entidade em baixo do bloco)
        else
        {
            pos.y += interseccao->height;
            pEnt->setVelocidadeY(0.0f);
        }
    }
    // Colisao horizontal (eixo X)
    else
    {
        // Colisao pela esquerda (entidade a direita do bloco)
        if (ent_colisao.left < bloco->left)
        {
            pos.x -= interseccao->width;
        }
        // Colisao pela direita (entidade a esquerda do bloco)
        else
        {
            pos.x += interseccao->width;
        }
    }

    // Aplica a nova posição e atualiza a caixa de colisão da entidade
    pEnt->setXY(pos);
}

void GerenciadorColisoes :: executar()
{
    tratarColisoesEnemObst();
    tratarColisoesJogInim();
    tratarColisoesJogObst();
}