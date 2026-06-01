#include "fase.hpp"
#include <iostream>

using namespace fases;

Fase :: Fase(const std::string& caminhoMapa) : minimo_ent(3)
{
    arquivo.open(caminhoMapa);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de mapa!" << std::endl;
    }
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

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxInimFaceis();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

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

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxPlataformas();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

    for (int i=0; i<qntd; i++)
    {
        Plataforma* plat = new Plataforma(posicoes[i].x, posicoes[i].y, PRATELEIRA);
        lista_ents.incluir(plat); 
        gc.incluirObstaculo(plat);
    }
}

void Fase :: criarAgua()// A no txt
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
            if (linha[x]=='A')//compara com o txt 
            {
                posicoes.push_back({x * 64, y * 64});
            }
        }
        y++;
    }

    std::mt19937 rng(time(nullptr));
    std::shuffle(posicoes.begin(), posicoes.end(), rng);
    
    int max = getMaxAgua();
    int qntd = rand() % ((int)posicoes.size() + 1);
    if (qntd<minimo_ent)
        qntd=minimo_ent;
    if (qntd>max)
        qntd=max;

    for (int i=0; i<qntd; i++)
    {
        Agua* agua = new Agua(posicoes[i].x, posicoes[i].y);
        lista_ents.incluir(agua); 
        gc.incluirObstaculo(agua);
    }
}

void Fase::criarCenario()
{
    std::string linha;
    int y = 0;

    while (std::getline(arquivo, linha))
    {
        for (int x = 0; x < linha.size(); x++)
        {
            if (linha[x]=='1')//compara com o txt
            {
                Bloco* bloco = new Bloco(x * 64, y * 64, 64, 16);
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
