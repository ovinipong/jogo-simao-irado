#include "fase.hpp"
#include <iostream>
#include <stdexcept>

using namespace fases;

Fase :: Fase(const std::string& caminhoMapa, Jogador* pJog1, Jogador* pJog2) : minimo_ent(3),
                                                                               maxInimFaceis(5),
                                                                               maxPlataformas(20),
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
    Bloco* fundo = new Bloco(0, 0, 1408, 576, FUNDO);
    fundo->inicializarSprite(caminhoFundo, 1, 1408, 576, 0, 0, 0, sf::Vector2f(0.f, -4.f));
    //nao incluir no g_colisoes
    lista_ents.incluir(fundo);

    Bloco* parededir = new Bloco(0, 0, 6, 576, PAREDE);
    lista_ents.incluir(parededir);
    gc.incluirBloco(parededir);

    Bloco* paredeesq = new Bloco(1405, 0, 6, 576, PAREDE);
    lista_ents.incluir(paredeesq);
    gc.incluirBloco(paredeesq);

    Bloco* teto = new Bloco(0, 0, 1408, 6, TETO);
    lista_ents.incluir(teto);
    gc.incluirBloco(teto);

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
                Bloco* bloco = new Bloco(x * 64, y * 64, 64, 44, CHAO);
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
    pGG->mostrarVida(pJogador1->getVida(), pJogador2->getVida(), pJogador2->getValido());
    pGG->mostrarPontos(pJogador1->getPontos(), pJogador2->getPontos(), pJogador2->getValido());
    
    ajustarProjeteisJogador();          // Coloca para fora os projeteis que nao estao na tela

    pGG->mostrar();                     // Da display na tela
}

void Fase::move_camera()
{
    sf::Vector2f pos_camera;
    sf::Vector2f pos_jog1 = pJogador1->getColisao().getPosition();
    sf::Vector2f pos_jog2 = pJogador2->getColisao().getPosition();
    if (pJogador1->getValido() && !(pJogador2->getValido()))
    {
        pos_camera.x = pos_jog1.x + 32;
    }
    else if (!(pJogador1->getValido()) && pJogador2->getValido())
    {
        pos_camera.x = pos_jog2.x + 32;
    }
    else
    {
        pos_camera.x = ((pos_jog1.x + pos_jog2.x) / 2) + 32;
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
            (*it)->setDonoRato(NULL);
        }
    }
}

void Fase :: carregarFase()
{
    std::ifstream arquivo_save("assets/salvar/salvar_fase.txt", std::ios::in);

    if (!arquivo_save.is_open())
    {
        std::cerr << "Arquivo de jogo salvo nao encontrado ou nao pode ser aberto!" << std::endl;
        return;
    }

    int id_entidade;

    lista_ents.limpar();

    // Cria o cenario depois de limpar a fase
    criarCenario("assets/fundofase1.png");

    std::map<int, Rato*> mapa_ratos;
    std::vector<std::pair<Projetil*, int>> projeteis_donos_carregados;

    // Percorre levando em conta o id
    while ( arquivo_save >> id_entidade)
    {
        switch(id_entidade)
        {
            // Primeiro Jogador
            case(2):
            {
                int x, y, pontos, num_vidas;
                float velocidade_y;
                arquivo_save >> x >> y >> num_vidas >> pontos >> velocidade_y;
                pJogador1->setXY(x, y);
                pJogador1->setVida(num_vidas);
                pJogador1->setPontos(pontos);
                pJogador1->setVelocidadeY(velocidade_y);
                
                gc.incluirJogadores(pJogador1);
                lista_ents.incluir(pJogador1);
                break;
            }
            // Bolinho
            case(3):
            {
                int x, y, num_vidas, move_speed;
                float velocidade_y;
                arquivo_save >> x >> y >> num_vidas >> velocidade_y >> move_speed;
                Bolinho *pBolinho = new Bolinho(x, y);
                pBolinho->setVida(num_vidas);
                pBolinho->setVelocidadeY(velocidade_y);
                pBolinho->setMoveSpeed(move_speed);

                gc.incluirInimigo(pBolinho);
                lista_ents.incluir(pBolinho);
                break;
            }
            // Bolo
            case(4):
            {
                int x, y, num_vidas, velocidade_x, estado;
                float velocidade_y;
                arquivo_save >> x >> y >> num_vidas >> velocidade_x >> velocidade_y >> estado;
                Bolo *pBolo = new Bolo(x, y);
                pBolo->setVida(num_vidas);
                pBolo->setVelocidadeX(velocidade_x);
                pBolo->setVelocidadeY(velocidade_y);
                pBolo->setEstado(static_cast<entidades::EstadoBolo>(estado));

                gc.incluirInimigo(pBolo);
                lista_ents.incluir(pBolo);
                break;
            }
            // Rato
            case(5):
            {
                int x, y, num_vidas, id_instancia;
                arquivo_save >> x >> y >> num_vidas >> id_instancia;
                Rato *pRato = new Rato(x, y, pJogador1);
                pRato->setVida(num_vidas);

                gc.incluirInimigo(pRato);
                lista_ents.incluir(pRato);
                mapa_ratos[id_instancia] = pRato;
                break;
            }
            // Projetil jogador
            case(6):
            {
                int x, y;
                bool ativo;
                float velocidade_x, velocidade_y, mhs;
                arquivo_save >> x >> y >> ativo >> velocidade_x >> velocidade_y >> mhs;
                Projetil *pProj = new Projetil(x, y, JOGADOR);
                if (ativo) pProj->setAtivo(); else pProj->setInativo();
                pProj->setXY(x, y);
                pProj->setVelocidadeX(velocidade_x);
                pProj->setVelocidadeY(velocidade_y);
                pProj->setTempoMhs(mhs);

                gc.incluirProjetil(pProj);
                lista_ents.incluir(pProj);
                projeteis_jogador.push_back(pProj);
                break;
            }
            // Plataforma
            case(7):
            {
                int x, y;
                arquivo_save >> x >> y;
                Plataforma *pPlat = new Plataforma(x, y, PRATELEIRA);
                pPlat->setXY(x, y);

                gc.incluirObstaculo(pPlat);
                lista_ents.incluir(pPlat);
                break;
            }
            // Mesa
            case(8):
            {
                int x, y;
                arquivo_save >> x >> y;
                Plataforma *pPlat = new Plataforma (x, y, MESA);
                gc.incluirObstaculo(pPlat);
                lista_ents.incluir(pPlat);
                break;
            }
            // Cristaleira
            case(9):
            {
                int x, y;
                arquivo_save >> x >> y;
                Plataforma *pPlat = new Plataforma (x, y, CRISTALEIRA);

                gc.incluirObstaculo(pPlat);
                lista_ents.incluir(pPlat);
                break;
            }
            // Agua
            case(10):
            {
                int x, y;
                arquivo_save >> x >> y;
                Agua *pAgua = new Agua(x, y);

                gc.incluirObstaculo(pAgua);
                lista_ents.incluir(pAgua);
                break;
            }
            // Lustre
            case(11):
            {
                int x, y;
                bool caindo;
                float y_incial, velocidade_y;
                arquivo_save >> x >> y >> caindo >> y_incial >> velocidade_y;
                Lustre *pLustre = new Lustre(x, y);
                pLustre->setCaindo(caindo);
                pLustre->setYInicial(y_incial);
                pLustre->setVelocidadeY(velocidade_y);

                gc.incluirObstaculo(pLustre);
                lista_ents.incluir(pLustre);
                break;
            }
            // Segundo jogador
            case(12):
            {
                int x, y, pontos, num_vidas;
                float velocidade_y;
                arquivo_save >> x >> y >> num_vidas >> pontos >> velocidade_y;
                pJogador2->setXY(x, y);
                pJogador2->setVida(num_vidas);
                pJogador2->setPontos(pontos);
                pJogador2->setVelocidadeY(velocidade_y);
                
                gc.incluirJogadores(pJogador2);
                lista_ents.incluir(pJogador2);
                break;
            }
            // Projetil Rato
            case(13):
            {
                int x, y, id_dono;
                bool ativo;
                float velocidade_x, velocidade_y, mhs, y_inicial_mhs;
                arquivo_save >> x >> y >> ativo >> velocidade_x >> velocidade_y >> mhs >> y_inicial_mhs >> id_dono;
                Projetil *pProj = new Projetil(x, y, RATO);

                if (ativo)
                {
                    pProj->setAtivo();
                    pProj->setXY(x, y);
                }
                else
                {
                    pProj->setInativo();
                }

                pProj->setVelocidadeX(velocidade_x);
                pProj->setVelocidadeY(velocidade_y);
                pProj->setTempoMhs(mhs);
                pProj->setYInicialMhs(y_inicial_mhs);
                projeteis_donos_carregados.push_back({pProj, id_dono});


                gc.incluirProjetil(pProj);
                lista_ents.incluir(pProj);
                projeteis_rato.push_back(pProj);
                break;
            }
        }
    }
    
    pJogador1->setListaProjeteis(&projeteis_jogador);

    for (auto& par : mapa_ratos)
    {
        par.second->setListaProjeteis(&projeteis_rato);
    }

    for (auto& par : projeteis_donos_carregados)
    {
        Projetil* pProj = par.first;
        int id_dono = par.second;

        auto it = mapa_ratos.find(id_dono);
        if (it != mapa_ratos.end())
        {
            pProj->setDonoRato(it->second);
        }
        else
        {
            pProj->setDonoRato(NULL);
        }
    }
    arquivo_save.close();
}