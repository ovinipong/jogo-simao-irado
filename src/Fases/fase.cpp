#include "fase.hpp"
#include <iostream>

using namespace fases;

Fase :: Fase(const std::string& caminhoMapa, Jogador* pJog) : minimo_ent(3),
                                                            maxInimFaceis(5),
                                                            maxPlataformas(5)
{
    pJogador = pJog;

    arquivo.open(caminhoMapa);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de mapa!" << std::endl;
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

Fase :: ~Fase()
{
    arquivo.close();
}

void Fase :: criarInimFaceis()//F no txt
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
        InimigoFacil* inim = new InimigoFacil(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(inim); 
        gc.incluirInimigo(inim);
    }
}

void Fase :: criarPlataformas()//P M C no txt
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
            if (linha[x]=='P')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});
            }
            if (linha[x]=='M')//compara com o txt 
            {
                Plataforma* plat = new Plataforma(x*64, y*64, MESA);
                lista_ents.incluir(plat); 
                gc.incluirObstaculo(plat);
            }
            if (linha[x]=='C')//compara com o txt 
            {
                Plataforma* plat = new Plataforma(x*64, y*64, CRISTALEIRA);
                lista_ents.incluir(plat); 
                gc.incluirObstaculo(plat);
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
        Plataforma* plat = new Plataforma(posicoes[i].x, posicoes[i].y, PRATELEIRA);
        lista_ents.incluir(plat); 
        gc.incluirObstaculo(plat);
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
    pGG->executar();                    // Limpa tela
    lista_ents.percorrer();             // Percorre executando
    gc.executar();                      // Ajusta a colisao
    lista_ents.percorrer_desenhar();    // Desenha na posicao correta
    pGG->mostrar();                     // Da display na tela
}

void Fase::move_camera()
{
    sf::Vector2f pos_camera = pJogador->getColisao().getPosition();
    pos_camera.x += 32;

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
        Projetil* proj = new Projetil(-100, -100);
        lista_ents.incluir(proj); 
        gc.incluirProjetil(proj);
        projeteis_jogador.push_back(proj);
    }
    
    pJogador->setListaProjeteis(&projeteis_jogador);
}
