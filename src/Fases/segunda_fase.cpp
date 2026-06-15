#include "segunda_fase.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

SegundaFase :: SegundaFase(Jogador *pJog1, Jogador* pJog2): Fase("assets/mapas/mapa2.txt", pJog1, pJog2),
                                                            maxInimRato(5),
                                                            maxLustre(5)
{
    srand(time(nullptr));
    criarCenario("assets/fundo1.png");
    criarInimigos();
    criarObstaculos();
    lista_ents.incluir(pJog1);
    gc.incluirJogadores(pJog1);
    if (pJog2->getValido()==true)//opção de 2 jogadores selecionada no menu
    {
        lista_ents.incluir(pJog2);
        gc.incluirJogadores(pJog2);
    }
    criarProjeteisJogador();
    criarProjeteisRatos();
}

SegundaFase :: ~SegundaFase()
{
    lista_ents.limpar();
}


void SegundaFase :: criarInimRatos()
{
    arquivo.clear();
    arquivo.seekg(0);

    std::vector<sf::Vector2i> posicoes;
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {   
            if (linha[x]=='R')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});

            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxInimRato();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

    if (qntd > (int)posicoes.size())
    {
        qntd = (int)posicoes.size();
    }


    for (int i=0; i<qntd; i++)
    {
        Rato* inim = new Rato(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(inim); 
        gc.incluirInimigo(inim);
        inim->setListaProjeteis(&projeteis_rato);
    }

}

void SegundaFase :: criarObstLustres()
{
    arquivo.clear();
    arquivo.seekg(0);

    std::vector<sf::Vector2i> posicoes;
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {   
            if (linha[x]=='L')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});
            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxLustre();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

    if (qntd > (int)posicoes.size())
    {
        qntd = (int)posicoes.size();
    }


    for (int i=0; i<qntd; i++)
    {
        Lustre* obstaculo = new Lustre(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(obstaculo); 
        gc.incluirObstaculo(obstaculo);
    }
}


void SegundaFase :: criarInimigos()
{
    criarInimBolinhos();
    criarInimRatos();
}

void SegundaFase :: criarObstaculos()
{
    criarPlataformas();
    criarObstLustres(); //Esta comentado porque eles nao existem
}

void SegundaFase :: executar()
{
    ajustarProjeteisRatos();
    Fase::executar();
    move_camera();
    if ((pJogador1->getXY().x >= 2200) && (pJogador2->getXY().x >=2200))
        concluida = true;
}

void SegundaFase :: criarProjeteisRatos()
{
    for (int i = 0; i < 10; i++)
    {
        Projetil* proj = new Projetil(-100, -100, RATO);
        gc.incluirProjetil(proj);
        lista_ents.incluir(proj);
        projeteis_rato.push_back(proj);
    }
}

void SegundaFase :: ajustarProjeteisRatos()
{
    // Verifica se nao esta vazia o vector
    if (projeteis_rato.empty()) return;

    // Pega a camera, tamanho e centro
    sf::View camera = pGG->getCamera();
    sf::Vector2f centro = camera.getCenter();
    sf::Vector2f tamanho = camera.getSize();

    // Pega a area que a camera esta
    sf::FloatRect area_camera;
    area_camera.left = centro.x - (tamanho.x / 2.0f);
    area_camera.top = centro.y - (tamanho.y / 2.0f);
    area_camera.width = tamanho.x;
    area_camera.height = tamanho.y;

    // Percorre o vector
    std::vector<Projetil *>::iterator it;
    for (it = projeteis_rato.begin(); it != projeteis_rato.end(); ++it)
    {
        // Verifica se nao esta colidindo com a area de tela e se esta ativo
        if (!area_camera.intersects((*it)->getColisao().getGlobalBounds()) && (*it)->getAtivo())
        {
            // std::cout << "FIQUEI DESATIVADO" << std::endl;
            (*it)->setInativo();
            (*it)->setXY(sf::Vector2f(-100.f, -100.f)); 
        }
    }
}