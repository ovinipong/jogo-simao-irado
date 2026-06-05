#include "menu.hpp"
#include "jogo.hpp"
#include <iostream>

using namespace sf;

Menu::Menu(Jogo* pJ) : pJogo(pJ)
{
    pFig = new Figura("assets/menu_fundo.png");
    pFig->frame_atual= 0;
    pFig->total_frames= 1;   
    pFig->frame_largura=640;
    pFig->frame_altura=480;  
    pFig->contador= 0;
    pFig->v_animacao= 0;// troca de frame a cada 8 ticks

    tela = PRINCIPAL;
    
    if (!fonte.loadFromFile("assets/m6x11.ttf"))
    {
        std::cerr << "Erro ao carregar a fonte assets/m6x11.ttf!" << std::endl;
    }
}

Menu::~Menu()
{

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
    sf::RenderWindow* window = Ente::getGG()->window; 
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
                    tela = SELECAO_FASE; 
                }
                else if (btnRanking.getGlobalBounds().contains(mousePosF))
                {
                    tela = PONTUACAO;
                }
            }
            else if (tela == SELECAO_FASE)
            {
                if (btnFase1.getGlobalBounds().contains(mousePosF))
                {
                    pJogo->setEstado(PRIMEIRA_FASE); 
                }
                else if (btnFase2.getGlobalBounds().contains(mousePosF))
                {
                    pJogo->setEstado(PRIMEIRA_FASE); 
                }
                else if (btnVoltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = PRINCIPAL;
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
    }
    else if (tela == PONTUACAO)
    {
        window->draw(txtTituloRanking);
        window->draw(btnVoltar);
        window->draw(txtVoltar);
    }
}