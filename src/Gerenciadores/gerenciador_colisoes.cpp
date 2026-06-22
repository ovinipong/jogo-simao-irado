#include "gerenciador_colisoes.hpp"
#include "rato.hpp"

using namespace gerenciadores;
using namespace std;
using namespace sf;
using namespace entidades;

GerenciadorColisoes :: GerenciadorColisoes() 
{ 

}

GerenciadorColisoes :: ~GerenciadorColisoes()
{

}

/* =============================================== */
/* =============== TRATAR COLISOES =============== */
/* =============================================== */

void GerenciadorColisoes :: tratarColisoesJogObst()
{
    std::vector<Jogador*>::iterator it1;
    std::list<Obstaculo*>::iterator it2;

    for (it1 =jogadores.begin(); it1 != jogadores.end(); ++it1)
    {
        if((*it1)->getValido()==false) continue; //ignora a iteração sobre esse jogador
        for (it2 = obstaculos.begin(); it2 != obstaculos.end(); ++it2)
        {
            FloatRect interseccao;
            FloatRect jogador_colisao = (*it1)->getColisao().getGlobalBounds();
            FloatRect bloco_colisao = (*it2)->getColisao().getGlobalBounds();

            // Se estiver colidindo
            if (jogador_colisao.intersects(bloco_colisao, interseccao))
            {
                (*it2)->obstaculizar(*it1);
            }
        }        
    }
}

void GerenciadorColisoes :: tratarColisoesJogInim()
{
    std::vector<Jogador*>::iterator it1;
    std::vector<Inimigo*>::iterator it2;

    for(it1 =jogadores.begin(); it1 != jogadores.end(); ++it1)
    {
        if((*it1)->getValido()==false) continue; //ignora a iteração sobre esse jogador
        if((*it1)->getInvulneravel()==true) continue;  //ignora a iteração sobre esse jogador
        for (it2=inimigos.begin(); it2 != inimigos.end(); it2++)
        {
            if ((*it2)->getValido())
            {
                if(verificarColisao(*it1, *it2))
                {
                    (*it1)->reverterPosicao();
                    (*it1)->setInvulneravel();
                    (*it2)->danificar(*it1);
                }
            }
        }        
    }
}

void GerenciadorColisoes :: tratarColisoesInimObst()
{
    std::list<Obstaculo*>::iterator it1;
    std::vector<Inimigo *>::iterator it2;
    for (it1 = obstaculos.begin(); it1 != obstaculos.end(); ++it1)
    {
        for (it2 = inimigos.begin(); it2 != inimigos.end(); ++it2)
        {
            FloatRect interseccao;
            FloatRect inimigo_colisao = (*it2)->getColisao().getGlobalBounds();
            FloatRect obst_colisao = (*it1)->getColisao().getGlobalBounds();

            // Se estiver colidindo
            if (inimigo_colisao.intersects(obst_colisao, interseccao))
            {
                (*it1)->obstaculizar(*it2, &obst_colisao, &interseccao);
            }
        }
    }
}

void GerenciadorColisoes :: tratarColisioesJogBloco()
{
    std::vector<Jogador*>:: iterator it1;
    std::vector<Bloco*>::iterator it2;

    for(it1 =jogadores.begin(); it1 != jogadores.end(); ++it1)
    {
        if((*it1)->getValido()==false) continue; //ignora a iteração sobre esse jogador
        for (it2 = blocos.begin(); it2 != blocos.end(); it2++)
        {
            if (verificarColisao((*it2), (*it1)))
            {
                (*it2)->colisaoBloco(*it1);
            }
        }
    }
}

void GerenciadorColisoes :: tratarColisoesInimBloco()
{
    std::vector<Inimigo*>::iterator it1;
    std::vector<Bloco *>::iterator it2;
    for (it1 = inimigos.begin(); it1 != inimigos.end(); ++it1)
    {
        for (it2 = blocos.begin(); it2 != blocos.end(); ++it2)
        {
            FloatRect interseccao;
            FloatRect inimigo_colisao = (*it1)->getColisao().getGlobalBounds();
            FloatRect bloco_colisao = (*it2)->getColisao().getGlobalBounds();

            // Se estiver colidindo
            if (inimigo_colisao.intersects(bloco_colisao, interseccao))
            {
                (*it2)->colisaoBloco(*it1);
            }
            if (interseccao.height > interseccao.width)
            {
                (*it1)->inverterDirecao();
            }
        }
    }
}

void GerenciadorColisoes :: tratarColisoesInimProj()
{
    // Percorre todos os inimigos
    for (int i = 0; i < inimigos.size(); i++)
    {
        Inimigo* pInimigo = inimigos[i];

        // Se o inimigo já estiver morto, não precisa testar colisão com ele
        if (!pInimigo->getValido()) 
            continue;

        sf::FloatRect inim_colisao = pInimigo->getColisao().getGlobalBounds();

        // Percorre todos os projéteis guardados no Set
        std::set<Projetil*>::iterator it;
        for (it = projeteis.begin(); it != projeteis.end(); ++it)
        {
            Projetil* pProj = *it;

            // Só testa a colisão se o projétil estiver voando pela tela (ativo)
            if (!pProj->getAtivo() || pProj->getTipoProjetil() != JOGADOR) 
                continue;

            sf::FloatRect proj_colisao = pProj->getColisao().getGlobalBounds();

            // Verifica se a caixa de colisão do projétil encostou no inimigo
            if (inim_colisao.intersects(proj_colisao))
            {
                pProj->setAtivo();
                pProj->setXY(sf::Vector2f(-100.f, -100.f)); 

                if((*pInimigo).get_vida()==1)
                {
                    if ((pProj)->getProjJog1()==true)
                    {
                        if (jogadores.size()>0)
                            jogadores[0]->operator++();
                    }
                    else 
                    {
                        if(jogadores.size()>1)
                            jogadores[1]->operator++();
                    }
                }
                (*pInimigo).receberDano(1); 
            }
        }
    }
}


void GerenciadorColisoes :: tratarColisoesJogProj()
{
    vector<Jogador*>:: iterator it1;
    std::set<Projetil*>::iterator it2;

    for(it1 =jogadores.begin(); it1 != jogadores.end(); ++it1)
    {
        if((*it1)->getValido()==false) continue; //ignora a iteração sobre esse jogador
        if((*it1)->getInvulneravel()==true) continue; //ignora a iteraçãao sobre esse jogador
        for (it2 = projeteis.begin(); it2 != projeteis.end(); ++it2)
        {
            Projetil* pProj = *it2;

            // Só testa a colisão se o projétil estiver voando pela tela (ativo)
            if (!pProj->getAtivo() || pProj->getTipoProjetil() == JOGADOR) 
                continue;

            sf::FloatRect proj_colisao = pProj->getColisao().getGlobalBounds();
            sf::FloatRect jog_colisao = (*it1)->getColisao().getGlobalBounds();

            if (jog_colisao.intersects(proj_colisao))
            {
                pProj->getDonoRato()->zerarTimerAtirar();
                pProj->setInativo();

                (*it1)->receberDano(1); 
                (*it1)->setInvulneravel();
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesObstBloco()
{
    std::list <Obstaculo*>::iterator it1;
    std::vector <Bloco*>::iterator it2;
    for (it1 = obstaculos.begin(); it1 != obstaculos.end(); ++it1)
    {
        for (it2 = blocos.begin(); it2 != blocos.end(); ++it2)
        {
            FloatRect interseccao;
            FloatRect obstaculo_colisao = (*it1)->getColisao().getGlobalBounds();
            FloatRect bloco_colisao = (*it2)->getColisao().getGlobalBounds();

            // Se estiver colidindo
            if (obstaculo_colisao.intersects(bloco_colisao, interseccao))
            {
                (*it2)->colisaoBloco(*it1);
            }
        }
    }

}


/* ============================================================ */
/* =============== INCLUIR E REMOVER NAS LISTAS =============== */
/* ============================================================ */

void GerenciadorColisoes :: incluirInimigo (Inimigo *pi)
{
    inimigos.push_back(pi);
}

void GerenciadorColisoes :: incluirJogadores(Jogador *pj)
{
    jogadores.push_back(pj);
}

void GerenciadorColisoes :: incluirObstaculo(Obstaculo *po)
{
    obstaculos.push_back(po);
}

void GerenciadorColisoes :: incluirBloco(Bloco *pb)
{
    if (pb != nullptr) blocos.push_back(pb);
}

void GerenciadorColisoes :: incluirProjetil(Projetil *pp)
{
    if (pp != nullptr) projeteis.insert(pp);
}

void GerenciadorColisoes :: removerInimigo(Inimigo *pi)
{
    std::vector<Inimigo*>::iterator it;
    for (it = inimigos.begin(); it != inimigos.end(); ++it)
    {
        if (*it == pi)
        {
            inimigos.erase(it);
            break;
        }
    }
}

void GerenciadorColisoes :: removerJogador(Jogador *pj)
{
    std::vector<Jogador*>::iterator it;
    for (it = jogadores.begin(); it != jogadores.end(); ++it)
    {
        if (*it == pj)
        {
            jogadores.erase(it);
            break;
        }
    }
}

void GerenciadorColisoes :: removerObstaculo(Obstaculo *po)
{
    obstaculos.remove(po);
}

/* ============================================================ */
/* =============== VERIFICAR VALIDADE ENTIDADES =============== */
/* ============================================================ */

void GerenciadorColisoes :: verificaInimigos()
{
    std::vector<Inimigo*> mortos;
    std::vector<Inimigo*>::iterator it1;
    std::vector<Inimigo*>::iterator it2;

    for (it1 = inimigos.begin(); it1 != inimigos.end(); ++it1)
    {
        if ((*it1)->getValido() == false)
        {
            mortos.push_back(*it1);
        }
    }

    for (it2 = mortos.begin(); it2 != mortos.end(); ++it2)
    {
        removerInimigo(*it2);
    }
}

void GerenciadorColisoes :: verificaJogadores()
{
    std::vector<Jogador*> mortos;
    std::vector<Jogador*>::iterator it1;
    std::vector<Jogador*>::iterator it2;

    for (it1 = jogadores.begin(); it1 != jogadores.end(); ++it1)
    {
        if ((*it1)->getValido() == false)
        {
            mortos.push_back(*it1);
        }
    }

    for (it2 = mortos.begin(); it2 != mortos.end(); ++it2)
    {
        removerJogador(*it2);
    }
}

void GerenciadorColisoes :: verificaObstaculos()
{
    std::vector<Obstaculo*> mortos;
    std::list<Obstaculo*>::iterator it1;
    std::vector<Obstaculo*>::iterator it2;

    for (it1 = obstaculos.begin(); it1 != obstaculos.end(); ++it1)
    {
        if ((*it1)->getValido() == false)
        {
            mortos.push_back(*it1);
        }
    }

    for (it2 = mortos.begin(); it2 != mortos.end(); ++it2)
    {
        removerObstaculo(*it2);
    }
}

/* ===================================================== */
/* =============== VERIFICAR AS COLISOES =============== */
/* ===================================================== */

const bool GerenciadorColisoes :: verificarColisao (Entidade *pe1, Entidade *pe2)
{
    if (pe1->getColisao().getGlobalBounds().intersects(pe2->getColisao().getGlobalBounds()))
        return true;
    else 
        return false;
}

/* ======================================== */
/* =============== EXECUTAR =============== */
/* ======================================== */

void GerenciadorColisoes :: executar()
{
    tratarColisoesInimObst();
    tratarColisoesJogInim();
    tratarColisoesJogObst();
    tratarColisioesJogBloco();
    tratarColisoesInimBloco();
    tratarColisoesInimProj();
    tratarColisoesJogProj();
    tratarColisoesObstBloco();
    verificaInimigos();
    verificaJogadores();
    verificaObstaculos();
}