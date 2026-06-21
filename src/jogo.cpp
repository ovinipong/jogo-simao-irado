#include "jogo.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Jogo :: Jogo() : pJog1 (NULL), pJog2(NULL), menu(this), fase1(NULL), fase2(NULL)
{
    Ente::setGG(&gg);
    pJog1 = new Jogador(64, 400, false);
    pJog2 = new Jogador(64, 400, true);

    estado = MENU;
    estado_anterior = MENU;
    dois_jogadores = false;
}

Jogo :: ~Jogo()
{
    pJog1=NULL;
    fase1=NULL;
    fase2=NULL;
}

void Jogo :: executar()
{
    while (gg.janelaAberta())
    {
        switch(estado)
        {
            case(PRIMEIRA_FASE):
            {
                gg.setPausado(false);
                if (!fase1)
                {
                    // Apenas um jogador
                    if (!dois_jogadores)
                    {
                        pJog1->setXY(sf::Vector2f(64, 400));
                        pJog2->setInvalido();
                    }
                    // Os dois jogadores
                    else
                    {
                        pJog1->setXY(sf::Vector2f(64, 400));
                        pJog2->setXY(sf::Vector2f(64, 400));
                        pJog2->setValido();
                    }
                    fase1 = new PrimeiraFase(pJog1, pJog2);
                }
                fase1->executar();
                if (fase1->getConcluida())
                {
                    delete fase1;
                    fase1 = NULL;
                    std::cout << "trocando pra fase 2" << std::endl;
                    pJog1->setVida(40);
                    pJog2->setVida(40);
                    pJog1->setValido();
                    pJog2->setValido();
                    estado = SEGUNDA_FASE;
                }
                if (!pJog1->getValido() && !pJog2->getValido())
                {
                    std::cout << "jogador 1 morreu, voltando ao menu" << std::endl;
                    delete fase1;
                    fase1 = NULL;
                    delete pJog1;
                    delete pJog2;
                    pJog1 = new Jogador(64, 400, false);
                    pJog2 = new Jogador(64, 400, true);
                    estado = MENU;
                    menu.set_estado(SELECAO_FASE);
                }
                // Verifica se pausou o jogo
                if (gg.getPausado())
                {
                    menu.capturarFundo(gg.getWindow());

                    menu.set_estado(PAUSE);
                    estado_anterior = PRIMEIRA_FASE;
                    estado = PAUSADO;
                }

                // Verifica se pausou o jogo
                if (gg.getPausado())
                {
                    estado_anterior = PRIMEIRA_FASE;
                    estado = PAUSADO;
                }

                break;
            }
            case(SEGUNDA_FASE):
            {
                gg.setPausado(false);
                if (!fase2)
                {
                    // Apenas um jogador
                    if (!dois_jogadores)
                    {
                        pJog1->setXY(sf::Vector2f(64, 400));
                        pJog2->setInvalido();
                    }
                    // Os dois jogadores
                    else
                    {
                        pJog1->setXY(sf::Vector2f(64, 400));
                        pJog2->setXY(sf::Vector2f(64, 400));
                        pJog2->setValido();
                    }
                    fase2 = new SegundaFase(pJog1, pJog2);
                }
                fase2->executar();
                if (fase2->getConcluida())
                {
                    // Coloca a pontuacao no arquivo
                    ofstream arquivo;
                    arquivo.open("assets/pontos/pontuacao.txt", ios::app);
                    if (arquivo.is_open())
                    {
                        int pontos_total = (pJog1->getPontos()) + (pJog2->getPontos());
                        arquivo << menu.getNomeJogador() << ": " << pontos_total <<" pontos" << endl;
                        arquivo.close();
                    }
                    // Se der erro, printa a mensagem de erro
                    else
                    {
                        cerr << "Deu erro ao abrir o arquivo" << endl;
                    }

                    // Zera a pontuacao
                    pJog1->setPontos(0);
                    pJog2->setPontos(0);
                    pJog1->setVida(40);
                    pJog2->setVida(40);
                    delete fase2;
                    fase2 = NULL;
                    std::cout << "fase 2 concluída, retornando para o menu" << std::endl;
                    estado = MENU;
                    menu.set_estado(SELECAO_FASE);
                }
                if (!pJog1->getValido() && !pJog2->getValido())
                {
                    delete fase2;
                    fase2 = NULL;
                    //delete pJog1;
                    //delete pJog2;
                    pJog1 = new Jogador(64, 400, false);
                    pJog2 = new Jogador(64, 400, true);
                    estado = MENU;
                }

                // Verifica se pausou o jogo
                if (gg.getPausado())
                {
                    menu.capturarFundo(gg.getWindow());
                    
                    menu.set_estado(PAUSE);
                    estado_anterior = SEGUNDA_FASE;
                    estado = PAUSADO;
                }

                break;
            }
            case(MENU):
            {
                gg.centralizarCamera(sf::Vector2f(512.f, 288.f));
                gg.executar();
                menu.desenhar();
                menu.executar();
                gg.mostrar();
                break;
            }
            case(PAUSADO):
            {
                if (!gg.getPausado())
                {
                    estado = estado_anterior;
                }

                gg.centralizarCamera(sf::Vector2f(512.f, 288.f));
                gg.executar();
                menu.desenhar();
                menu.executar();
                gg.mostrar();
            }
        }   
    }
}

void Jogo :: setEstado(Estado e)
{
    estado = e;
}

void Jogo :: reiniciarFase()
{
    std::ofstream arquivo("assets/salvar/estado_jogo.txt", std::ios::out);

    if (!arquivo.is_open())
    {
        std::cerr << "Nao foi possivel salvar o arquivo estado_jogo.txt" << std::endl;
        return;
    }

    // Salva a fase que voce esta
    if (estado_anterior == PRIMEIRA_FASE)
    {
        arquivo << 1 << std::endl;
    }
    else if (estado_anterior == SEGUNDA_FASE)
    {
        arquivo << 2 << std::endl;
    }

    // Salva a quantidade de jogadores
    if (!dois_jogadores)
    {
        arquivo << 1 << std::endl;
    }
    else if (dois_jogadores)
    {
        arquivo << 2 << std::endl;
    }

    arquivo.close();

    // Salva
    if (estado_anterior == PRIMEIRA_FASE)
    {
        fase1->salvarEntidades();
    }
    else if (estado_anterior == SEGUNDA_FASE)
    {
        fase2->salvarEntidades();
    }

    if (fase1)
    {
        delete(fase1);
        fase1 = NULL;
    }
    if (fase2)
    {
        delete(fase2);
        fase2 = NULL;
    }
    if (pJog1)
    {
        delete(pJog1);
    }
    if (pJog2)
    {
        delete(pJog2);
    }

    pJog1 = new Jogador(400, 100, false);
    pJog2 = new Jogador(400, 100, true);
}

void Jogo :: voltarFase()
{
    std::ifstream arquivo("assets/salvar/estado_jogo.txt", std::ios::in);
    
    if (!arquivo.is_open())
    {
        std::cerr << "Nenhum save encontrado!" << std::endl;
        return;
    }

    int fase_salva = 1;
    int num_jogadores = 1;
    
    arquivo >> fase_salva >> num_jogadores;
    arquivo.close();

    dois_jogadores = (num_jogadores == 2);

    if (dois_jogadores) 
    {
        pJog2->setValido();
    } 
    else 
    {
        pJog2->setInvalido();
    }
    
    if (fase_salva == 1)
    {
        if (fase1) delete fase1;
        fase1 = new PrimeiraFase(pJog1, pJog2, true);
        estado = PRIMEIRA_FASE;
    }
    else if (fase_salva == 2)
    {
        if (fase2) delete fase2;
        fase2 = new SegundaFase(pJog1, pJog2, true);
        estado = SEGUNDA_FASE;
    }
}