#include "fase.hpp"
#include <iostream>
#include <stdexcept>

using namespace fases;

Fase :: Fase(const std::string& caminhoMapa, Jogador* pJog1, Jogador* pJog2) : minimo_ent(3),
                                                                               maxInimFaceis(5),
                                                                               maxPlataformas(5),
                                                                               concluida(false)
{
    pJogador1 = pJog1;
    pJogador2 = pJog2;

    try
    {
        arquivo.open(caminhoMapa);        
        
        if (!arquivo.is_open())
        {
            throw std::runtime_error("Nao foi possivel abrir o arquivo: " + caminhoMapa);
        }
        //Usado para padronizar a camera
        std::string linha;
        int colunas = 0, linhas = 0;
        while (std::getline(arquivo, linha)) {
            if ((int)linha.size() > colunas)
                colunas = linha.size();
            linhas++;
        }
        mapa_largura = colunas * 64.f;
        mapa_altura  = linhas  * 64.f;

    }
    catch(const std::exception& e)
    {
        std::cerr << "ERRO NA FASE!" << e.what() << '\n';
    }
}

Fase :: ~Fase()
{
    arquivo.close();
}

void Fase :: criarInimBolinhos()//F no txt
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
            if (linha[x]=='F')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});

            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = maxInimFaceis;
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
        Bolinho* inim = new Bolinho(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(inim); 
        gc.incluirInimigo(inim);
    }
}

void Fase :: criarPlataformas()//P M C no txt
{
    arquivo.clear();
    arquivo.seekg(0);

    std::vector<sf::Vector3i> posicoes;
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {   
            //2 prateleira, 3 mesa, 4 cristaleira
            if (linha[x]=='2')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64, 2});
            }
            else if (linha[x]=='3')
            {
                posicoes.push_back({x * 64, y * 64, 3});
            }
            else if (linha[x]=='4')
            {
                posicoes.push_back({x * 64, y * 64, 4});
            }
        }
        y++;
    }

    if (posicoes.empty()) return;

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = maxPlataformas;
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
        if (posicoes[i].z==2)
        {
           Plataforma* plat = new Plataforma(posicoes[i].x, posicoes[i].y, PRATELEIRA);
            lista_ents.incluir(plat); 
            gc.incluirObstaculo(plat); 
        }
        if (posicoes[i].z==3)
        {
            Plataforma* plat = new Plataforma(posicoes[i].x, posicoes[i].y, MESA);
            lista_ents.incluir(plat); 
            gc.incluirObstaculo(plat);
        }
        if (posicoes[i].z==4)
        {
            Plataforma* plat = new Plataforma(posicoes[i].x, posicoes[i].y, CRISTALEIRA);
            lista_ents.incluir(plat); 
            gc.incluirObstaculo(plat);
        }
    }
}

void Fase::criarCenario(const std::string& caminhoFundo)
{
    Bloco* fundo = new Bloco(0, 0, 1024, 576);
    fundo->inicializarSprite(caminhoFundo, 1, 1024, 576, 0, 0, 0, sf::Vector2f(0.f, 0.f));
    //nao incluir no g_colisoes
    lista_ents.incluir(fundo);

    arquivo.clear();
    arquivo.seekg(0);
    
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {
            if (linha[x]=='1')//compara com o txt
            {
                Bloco* bloco = new Bloco(x * 64, y * 64, 64, 32);
                lista_ents.incluir(bloco);
                gc.incluirBloco(bloco);
            }
        }
        y++;
    }
}

void Fase::executar()
{
    pJogador1->setListaProjeteis(&projeteis_jogador);
    pJogador2->setListaProjeteis(&projeteis_jogador);

    pGG->executar();                    // Limpa tela
    lista_ents.percorrer();             // Percorre executando
    gc.executar();                      // Ajusta a colisao
    lista_ents.percorrer_desenhar();    // Desenha na posicao correta
    pGG->mostrarVida(pJogador1->getVida());
    pGG->mostrarPontos(pJogador1->getPontos());
    
    ajustarProjeteisJogador();          // Coloca para fora os projeteis que nao estao na tela

    pGG->mostrar();                     // Da display na tela
}

void Fase::move_camera()
{
    sf::Vector2f pos_camera;
    sf::Vector2f pos_jog1 = pJogador1->getColisao().getPosition();
    
    if (pJogador2->getValido())
    {
        sf::Vector2f pos_jog2 = pJogador2->getColisao().getPosition();
        pos_camera.x = ((pos_jog1.x + pos_jog2.x) / 2) + 32;
    }
    else
    {
        pos_camera.x = pos_jog1.x + 32;
    }
    
    //usar igual no gerenciador grafico
    float view_largura = 1024.f;
    float view_altura  = 576.f;

    float limite_esquerda = view_largura / 2.f;
    float limite_direita  = mapa_largura - (view_largura / 2.f);

    pos_camera.x = std::max(limite_esquerda, std::min(pos_camera.x, limite_direita));
    pos_camera.y = mapa_altura / 2.f;

    pGG->centralizarCamera(pos_camera);
}

void Fase :: criarProjeteisJogador()
{
    for (int i = 0; i < 10; i++)
    {
        Projetil* proj = new Projetil(-100, -100, JOGADOR);
        lista_ents.incluir(proj); 
        gc.incluirProjetil(proj);
        projeteis_jogador.push_back(proj);
    }
    
    pJogador1->setListaProjeteis(&projeteis_jogador);
    pJogador2->setListaProjeteis(&projeteis_jogador);
}

void Fase :: ajustarProjeteisJogador()
{
    // Verifica se nao esta vazia o vector
    if (projeteis_jogador.empty()) return;

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
    for (it = projeteis_jogador.begin(); it != projeteis_jogador.end(); ++it)
    {
        // Verifica se nao esta colidindo com a area de tela e se esta ativo
        if (!area_camera.intersects((*it)->getColisao().getGlobalBounds()) && (*it)->getAtivo())
        {
            // std::cout << "FIQUEI DESATIVADO" << std::endl;
            (*it)->setInativo();
            (*it)->setOrigemProj(false);
            (*it)->setXY(sf::Vector2f(-100.f, -100.f)); 
        }
    }
}