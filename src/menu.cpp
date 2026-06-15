#include "menu.hpp"
#include "jogo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;

Menu::Menu(Jogo* pJ) : pJogo(pJ)
{
    inicializarSprite("assets/menu_fundo.png", 1, 640, 480, 0, 0, 0);

    tela = PRINCIPAL;
    
    if (!fonte.loadFromFile("assets/m6x11.ttf"))
    {
        std::cerr << "Erro ao carregar a fonte assets/m6x11.ttf!" << std::endl;
    }
    fase_escolhida = -1;
}

Menu::~Menu()
{

}

void Menu :: carregar_ranking()
{
    // Limpa o ranking
    ordem_ranking.clear();

    // Abre a pontuacao
    std::ifstream pontuacao("assets/pontos/pontuacao.txt");
    
    if (!pontuacao.is_open()) 
    {
        std::cerr << "Erro ao abrir o arquivo de pontuacao" << std::endl;
        return; 
    }
    
    std::string linha;
    
    // Percorre o txt linha por linha
    while(std::getline(pontuacao, linha)) 
    {
        // Acha a distancia ate os dois pontos
        size_t posicao_dois_pontos = linha.find(": ");
        if (posicao_dois_pontos != std::string::npos)
        {
            std::string nome = linha.substr(0, posicao_dois_pontos);

            size_t posicao_pontuacao = linha.find(" pontos", posicao_dois_pontos + 2);
            std::string string_pontos;
            
            if (posicao_pontuacao != std::string::npos) 
            {
                string_pontos = linha.substr(posicao_dois_pontos + 2, posicao_pontuacao - (posicao_dois_pontos + 2));
            }
            else
            {
                string_pontos = linha.substr(posicao_dois_pontos + 2);
            }

            int pontos = 0;
            try
            {
                pontos = std::stoi(string_pontos);
            }
            catch(...)
            {
                pontos = 0;
            }

            ordem_ranking.insert({pontos, nome});
        }
    }
    pontuacao.close();
}

void Menu::executar()
{
    // ---------------------------------------------------------
    // SETAR AS COISAS PARA OS BOTOES
    // ---------------------------------------------------------
    sf::RectangleShape btnJogar(sf::Vector2f(200.f, 50.f));
    sf::RectangleShape btnRanking(sf::Vector2f(200.f, 50.f));
    sf::RectangleShape btnFase1(sf::Vector2f(200.f, 50.f));
    sf::RectangleShape btnFase2(sf::Vector2f(200.f, 50.f));
    sf::RectangleShape btnVoltar(sf::Vector2f(200.f, 50.f));

    btnJogar.setPosition(220.f, 180.f);
    btnRanking.setPosition(220.f, 250.f);
    btnFase1.setPosition(220.f, 180.f);
    btnFase2.setPosition(220.f, 250.f);
    btnVoltar.setPosition(220.f, 380.f);

    btnJogar.setFillColor(sf::Color(50, 50, 200));
    btnRanking.setFillColor(sf::Color(50, 50, 200));
    btnFase1.setFillColor(sf::Color(50, 150, 50));
    btnFase2.setFillColor(sf::Color(50, 150, 50));
    btnVoltar.setFillColor(sf::Color(150, 50, 50));

    sf::RectangleShape btn1Jog(sf::Vector2f(200.f, 50.f));
    sf::RectangleShape btn2Jog(sf::Vector2f(200.f, 50.f));
    btn1Jog.setPosition(220.f, 180.f);
    btn2Jog.setPosition(220.f, 250.f);
    btn1Jog.setFillColor(sf::Color(50, 150, 50));
    btn2Jog.setFillColor(sf::Color(50, 150, 50));

    sf::Text txt1Jog("1 Jogador", fonte, 30);
    sf::Text txt2Jog("2 Jogadores", fonte, 30);
    txt1Jog.setPosition(btn1Jog.getPosition().x + 40.f, btn1Jog.getPosition().y + 8.f);
    txt2Jog.setPosition(btn2Jog.getPosition().x + 20.f, btn2Jog.getPosition().y + 8.f);
    txt1Jog.setFillColor(sf::Color::White);
    txt2Jog.setFillColor(sf::Color::White);

    // ---------------------------------------------------------
    // TEXTO NOS BOTOES
    // ---------------------------------------------------------
    sf::Text txtJogar("Jogar", fonte, 30);
    sf::Text txtRanking("Ranking", fonte, 30);
    sf::Text txtFase1("Fase 1", fonte, 30);
    sf::Text txtFase2("Fase 2", fonte, 30);
    sf::Text txtVoltar("Voltar", fonte, 30);
    sf::Text txtTituloRanking("RANKING GERAL", fonte, 40); // Texto para a tela de ranking

    txtJogar.setPosition(btnJogar.getPosition().x + 60.f, btnJogar.getPosition().y + 8.f);
    txtRanking.setPosition(btnRanking.getPosition().x + 45.f, btnRanking.getPosition().y + 8.f);
    txtFase1.setPosition(btnFase1.getPosition().x + 55.f, btnFase1.getPosition().y + 8.f);
    txtFase2.setPosition(btnFase2.getPosition().x + 55.f, btnFase2.getPosition().y + 8.f);
    txtVoltar.setPosition(btnVoltar.getPosition().x + 55.f, btnVoltar.getPosition().y + 8.f);
    txtTituloRanking.setPosition(200.f, 100.f); // Posição do título na tela vazia

    txtJogar.setFillColor(sf::Color::White);
    txtRanking.setFillColor(sf::Color::White);
    txtFase1.setFillColor(sf::Color::White);
    txtFase2.setFillColor(sf::Color::White);
    txtVoltar.setFillColor(sf::Color::White);
    txtTituloRanking.setFillColor(sf::Color::Yellow);

    // ---------------------------------------------------------
    // INTERACAO COM O MOUSE
    // ---------------------------------------------------------
    sf::RenderWindow* window = Ente::getGG()->getWindow(); 
    static bool mouseSegurado = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!mouseSegurado) 
        {
            mouseSegurado = true;
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosF = window->mapPixelToCoords(mousePos);

            if (tela == PRINCIPAL)
            {
                if (btnJogar.getGlobalBounds().contains(mousePosF))
                {
                    nome_jogador = "";
                    tela = SELECAO_FASE; 
                }
                else if (btnRanking.getGlobalBounds().contains(mousePosF))
                {
                    carregar_ranking();
                    tela = PONTUACAO;
                }
            }
            else if (tela == SELECAO_FASE)
            {
                if (btnFase1.getGlobalBounds().contains(mousePosF))
                {
                    fase_escolhida = 1;
                    tela = SELECAO_JOGADORES;
                }
                else if (btnFase2.getGlobalBounds().contains(mousePosF))
                {
                    fase_escolhida = 2;
                    tela = SELECAO_JOGADORES; 
                }
                else if (btnVoltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = PRINCIPAL;
                }
            }
            else if (tela == SELECAO_JOGADORES)
            {
                if (btn1Jog.getGlobalBounds().contains(mousePosF))
                {
                    pJogo->setDoisJogadores(false);
                    
                    if (fase_escolhida == 1)
                    {
                        pJogo->setEstado(PRIMEIRA_FASE);
                    }
                    else if (fase_escolhida == 2)
                    {
                        pJogo->setEstado(SEGUNDA_FASE);
                    }
                }
                else if (btn2Jog.getGlobalBounds().contains(mousePosF))
                {
                    pJogo->setDoisJogadores(true);
                    if (fase_escolhida == 1)
                    {
                        pJogo->setEstado(PRIMEIRA_FASE);
                    }
                    else if (fase_escolhida == 2)
                    {
                        pJogo->setEstado(SEGUNDA_FASE);
                    }
                }
                else if (btnVoltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = SELECAO_FASE;
                }
            }
            else if (tela == PONTUACAO)
            {
                if (btnVoltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = PRINCIPAL;
                }
            }
        }
    }
    else
    {
        mouseSegurado = false; 
    }

    // ---------------------------------------------------------
    // CAPTURA DO NOME DO JOGADOR
    // ---------------------------------------------------------
    if (tela == SELECAO_FASE)
    {
        GerenciadorGrafico* gg = Ente::getGG();

        // Verifica se o jogador apertou para apagar o nome dele
        if (gg->getBackspacePressionado() && !nome_jogador.empty()) 
        {
            // Apaga a ultima letra
            nome_jogador.pop_back();
        }
        // Adiciona as novas letras
        nome_jogador += gg->getTextoDigitado(); 
    }

    // ---------------------------------------------------------
    // DESENHAR AS COISAS NA TELA
    // ---------------------------------------------------------
    if (tela == PRINCIPAL)
    {
        window->draw(btnJogar);
        window->draw(txtJogar);
        window->draw(btnRanking);
        window->draw(txtRanking);
    }
    else if (tela == SELECAO_FASE)
    {
        window->draw(btnFase1);
        window->draw(txtFase1);
        window->draw(btnFase2);
        window->draw(txtFase2);
        window->draw(btnVoltar);
        window->draw(txtVoltar);
    
        // Desenhar as coisas do nome
        sf::Text texto_nome("Seu nome: " + nome_jogador + "_", fonte, 30);
        texto_nome.setPosition(220.f, 100.f);
        texto_nome.setFillColor(sf::Color::Yellow);
        window->draw(texto_nome);
    
    }
    else if (tela == PONTUACAO)
    {
        window->draw(txtTituloRanking);
        window->draw(btnVoltar);
        window->draw(txtVoltar);

        float posY = 180.f;
        int posicaoAtual = 1;

        // Se tiver ranking
        for (auto it = ordem_ranking.begin(); it != ordem_ranking.end() && posicaoAtual <= 5; ++it, posicaoAtual++)
        {
            std::string strExibicaoNome = std::to_string(posicaoAtual) + ". " + it->second;
            sf::Text txtColocado(strExibicaoNome, fonte, 26);
            txtColocado.setPosition(220.f, posY);
            txtColocado.setFillColor(sf::Color::White);
            window->draw(txtColocado);

            std::string strExibicaoPontos = std::to_string(it->first) + " pts";
            sf::Text txtPontos(strExibicaoPontos, fonte, 26);
            txtPontos.setPosition(460.f, posY);
            txtPontos.setFillColor(sf::Color::Cyan);
            window->draw(txtPontos);

            posY += 35.f;
            
        }

        // Se nao tiver ranking
        if (ordem_ranking.empty())
        {
            sf::Text txtVazio("Nenhum recorde registrado ainda!", fonte, 24);
            txtVazio.setPosition(220.f, 220.f);
            txtVazio.setFillColor(sf::Color(180, 180, 180));
            window->draw(txtVazio);
        }
    }
    else if (tela == SELECAO_JOGADORES)
    {
        window->draw(btn1Jog);
        window->draw(txt1Jog);
        window->draw(btn2Jog);
        window->draw(txt2Jog);
        window->draw(btnVoltar);
        window->draw(txtVoltar);
    }
}