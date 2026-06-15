#include "jogo.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Jogo :: Jogo() : pJog1 (NULL), pJog2(NULL), menu(this), fase1(NULL), fase2(NULL)
{
    Ente::setGG(&gg);
    pJog1 = new Jogador(400, 100, false);
    pJog2 = new Jogador(400, 100, true);

    estado = MENU;
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
                if (!fase1)
                {
                    pJog1->setXY(sf::Vector2f(400, 100));
                    pJog2->setXY(sf::Vector2f(400, 100));
                    fase1 = new PrimeiraFase(pJog1, pJog2);
                }
                fase1->executar();
                if (fase1->getConcluida())
                {
                    delete fase1;
                    fase1 = NULL;
                    std::cout << "trocando pra fase 2" << std::endl;
                    estado = SEGUNDA_FASE;
                }
                if (!pJog1->getValido() && !pJog2->getValido())
                {
                    std::cout << "jogador 1 morreu, voltando ao menu" << std::endl;
                    delete fase1;
                    fase1 = NULL;
                    delete pJog1;
                    delete pJog2;
                    pJog1 = new Jogador(400, 100, false);
                    pJog2 = new Jogador(400, 100, true);
                    estado = MENU;
                }

                break;
            }
            case(SEGUNDA_FASE):
            {
                if (!fase2)
                {
                    pJog1->setXY(sf::Vector2f(400, 100));
                    pJog2->setXY(sf::Vector2f(400, 100));
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
                        arquivo << menu.getNomeJogador() << ": " << pJog1->getPontos() <<" pontos" << endl;
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
                    delete fase2;
                    fase2 = NULL;
                    std::cout << "fase 2 concluída, retornando para o menu" << std::endl;
                    estado = MENU;
                }
                if (!pJog1->getValido() && !pJog2->getValido())
                {
                    delete fase2;
                    fase2 = NULL;
                    delete pJog1;
                    delete pJog2;
                    pJog1 = new Jogador(400, 100, false);
                    pJog2 = new Jogador(400, 100, true);
                    estado = MENU;
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
        }   
    }
}

void Jogo :: setEstado(Estado e)
{
    estado = e;
}