#include "menu.hpp"
#include "jogo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;

Menu::Menu(Jogo* pJ) : pJogo(pJ)
{
    inicializarSprite("assets/menu_fundo.png", 1, 1024, 576, 0, 0, 0);

    tela = PRINCIPAL;
    
    if (!fonte.loadFromFile("assets/m6x11.ttf"))
    {
        std::cerr << "Erro ao carregar a fonte assets/m6x11.ttf!" << std::endl;
    }
    fase_escolhida = -1;

    // Carrega as texturas dos botoes
    if (!btn_jogar.loadFromFile("assets/botoes/btn_jogar.png")) { std::cerr << "Erro ao abrir btn_jogar.png!" << std::endl; }
    if (!btn_ranking.loadFromFile("assets/botoes/btn_ranking.png")) { std::cerr << "Erro ao abrir btn_ranking.png!" << std::endl; }
    if (!btn_fase1.loadFromFile("assets/botoes/btn_fase1.png")) { std::cerr << "Erro ao abrir btn_fase1.png!" << std::endl; }
    if (!btn_fase2.loadFromFile("assets/botoes/btn_fase2.png")) { std::cerr << "Erro ao abrir btn_fase2.png!" << std::endl; }
    if (!btn_um_jogador.loadFromFile("assets/botoes/btn_um_jogador.png")) { std::cerr << "Erro ao abrir btn_um_jogador.png!" << std::endl; }
    if (!btn_dois_jogadores.loadFromFile("assets/botoes/btn_dois_jogadores.png")) { std::cerr << "Erro ao abrir btn_dois_jogadores.png!" << std::endl; }
    if (!btn_voltar.loadFromFile("assets/botoes/btn_voltar.png")) { std::cerr << "Erro ao abrir btn_voltar.png!" << std::endl; }
    if (!btn_menu.loadFromFile("assets/botoes/btn_pause_menu.png")) { std::cerr << "Erro ao abrir btn_pause_menu.png" << std::endl; }
    if (!btn_continuar.loadFromFile("assets/botoes/btn_pause_continuar.png")) { std::cerr << "Erro ao abrir btn_pause_continuar.png" << std::endl; }
    if (!btn_progresso.loadFromFile("assets/botoes/btn_recuperar_progresso.png")) { std::cerr << "Erro ao abrir btn_pause_continuar.png" << std::endl; }
    
    // Atribui as texturas aos sprites
    botao_jogar.setTexture(btn_jogar);
    botao_ranking.setTexture(btn_ranking);
    
    botao_fase1.setTexture(btn_fase1);
    botao_fase2.setTexture(btn_fase2);
    botao_fase_progresso.setTexture(btn_progresso);
    
    botao_um_jogador.setTexture(btn_um_jogador);
    botao_dois_jogadores.setTexture(btn_dois_jogadores);
    
    botao_ranking_voltar.setTexture(btn_voltar);
    botao_fase_voltar.setTexture(btn_voltar);
    botao_jogador_voltar.setTexture(btn_voltar);

    botao_pause_menu.setTexture(btn_menu);
    botao_pause_continuar.setTexture(btn_continuar);

    // Carrega a textura dos fundos
    if(!fnd_menu.loadFromFile("assets/menu_fundo.png")) { std::cerr << "Erro ao abrir o menu_fundo.png" << std::endl; }
    if(!fnd_fases.loadFromFile("assets/fases_fundo.png")) { std::cerr << "Erro ao abrir o fases_fundo.png" << std::endl; }
    if (!fnd_ranking.loadFromFile("assets/ranking_fundo.png")) { std::cerr << "Erro ao abrir o ranking_fundo.png" << std::endl; }
    if (!fnd_jogadores.loadFromFile("assets/jogadores_fundo.png")) { std::cerr << "Erro ao abrir o jogadores_fundo.png" << std::endl; }

    // Atribui as texturas aos fundos
    fundo_menu.setTexture(fnd_menu);
    fundo_fases.setTexture(fnd_fases);
    fundo_ranking.setTexture(fnd_ranking);
    fundo_jogadores.setTexture(fnd_jogadores);

    fundo_menu.setPosition(0.f, 0.f);
    fundo_fases.setPosition(0.f, 0.f);
    fundo_ranking.setPosition(0.f, 0.f);
    fundo_ranking.setPosition(0.f, 0.f);

    // Coloca a posicao certa de cada sprite
    // (Largura da tela / 2) - (Largura do botao / 2)
    float centro_x = 264.f;
    
    botao_jogar.setPosition(centro_x, 289.f);
    botao_ranking.setPosition(centro_x, 385.f);
    botao_ranking_voltar.setPosition(452, 510.f);
    
    botao_fase1.setPosition(centro_x, 217.f);
    botao_fase2.setPosition(centro_x, 305.f);
    botao_fase_voltar.setPosition(452, 510.f);
    botao_fase_progresso.setPosition(centro_x, 399.f);
    
    botao_um_jogador.setPosition(centro_x, 289.f);
    botao_dois_jogadores.setPosition(centro_x, 385.f);
    botao_jogador_voltar.setPosition(452, 510.f);

    botao_pause_continuar.setPosition(362, 289.f);
    botao_pause_menu.setPosition(362, 385.f);

    // Retangulo para o pause
    retangulo_escuro.setSize(sf::Vector2f(1024.f, 576.f));
    retangulo_escuro.setPosition(0.f, 0.f);
    retangulo_escuro.setFillColor(sf::Color(0, 0, 0, 150));
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

void Menu::capturarFundo(sf::RenderWindow* window)
{
    sf::Vector2u tamanho_janela = window->getSize();
    sf::Vector2f tamanaho_camera = window->getView().getSize();

    textura_fundo_pause.create(tamanho_janela.x, tamanho_janela.y);
    textura_fundo_pause.update(*window);
    
    sprite_fundo_pause.setTexture(textura_fundo_pause, true);
    
    float escala_x = tamanaho_camera.x / (float)tamanho_janela.x;
    float escala_y = tamanaho_camera.y / (float)tamanho_janela.y;
    sprite_fundo_pause.setScale(escala_x, escala_y);

    sprite_fundo_pause.setPosition(0.f, 0.f);
}

void Menu::executar()
{
    // ---------------------------------------------------------
    // INTERACAO COM O MOUSE E CLIQUES
    // ---------------------------------------------------------

    sf::RenderWindow* window = Ente::getGG()->getWindow(); 
    static bool mouseSegurado = false;

    // Verifica se o botao esquerdo do mouse foi pressionado
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Verifica se o mouse nao estava segurado antes
        // Isso porque, se o usuario segurar o mouse fora de um botao e depois colocar o mouse em cima do botao, nao vai ativar
        if (!mouseSegurado) 
        {
            mouseSegurado = true;
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosF = window->mapPixelToCoords(mousePos);

            if (tela == PRINCIPAL)
            {
                if (botao_jogar.getGlobalBounds().contains(mousePosF))
                {
                    nome_jogador = "";
                    tela = SELECAO_FASE;
                }
                else if (botao_ranking.getGlobalBounds().contains(mousePosF))
                {
                    carregar_ranking();
                    tela = PONTUACAO;
                }
            }
            else if (tela == SELECAO_FASE)
            {
                if (botao_fase1.getGlobalBounds().contains(mousePosF))
                {
                    fase_escolhida = 1;
                    tela = SELECAO_JOGADORES;
                }
                else if (botao_fase2.getGlobalBounds().contains(mousePosF))
                {
                    fase_escolhida = 2;
                    tela = SELECAO_JOGADORES; 
                }
                else if (botao_fase_progresso.getGlobalBounds().contains(mousePosF))
                {
                    pJogo->voltarFase();
                }
                else if (botao_fase_voltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = PRINCIPAL;
                }
            }
            else if (tela == SELECAO_JOGADORES)
            {
                if (botao_um_jogador.getGlobalBounds().contains(mousePosF))
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
                else if (botao_dois_jogadores.getGlobalBounds().contains(mousePosF))
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
                else if (botao_jogador_voltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = SELECAO_FASE;
                }
            }
            else if (tela == PONTUACAO)
            {
                if (botao_ranking_voltar.getGlobalBounds().contains(mousePosF))
                {
                    tela = PRINCIPAL;
                }
            }
            else if (tela == PAUSE)
            {
                if (botao_pause_menu.getGlobalBounds().contains(mousePosF))
                {
                    tela = SELECAO_FASE;
                    pJogo->reiniciarFase();
                    pJogo->setEstado(MENU);
                }
                else if (botao_pause_continuar.getGlobalBounds().contains(mousePosF))
                {
                    pJogo->continuarFase();
                }
            }
        }
    }
    else
    {
        mouseSegurado = false; 
    }

    // ---------------------------------------------------------
    // LÓGICA DE CAPTURA DO NOME DO JOGADOR
    // ---------------------------------------------------------
    if (tela == SELECAO_FASE)
    {
        GerenciadorGrafico* gg = Ente::getGG();

        // Apaga o texto se o usuario apertar para apagar
        if (gg->getBackspacePressionado() && !nome_jogador.empty()) 
        {
            nome_jogador.pop_back();
        }

        // Soma o texto digitado ao nome
        nome_jogador += gg->getTextoDigitado(); 
    }

    // ---------------------------------------------------------
    // DESENHAR AS COISAS NA TELA
    // ---------------------------------------------------------
    if (tela == PRINCIPAL)
    {
        window->draw(fundo_menu);
        window->draw(botao_jogar);
        window->draw(botao_ranking);
    }
    else if (tela == SELECAO_FASE)
    {
        window->draw(fundo_fases);
        window->draw(botao_fase1);
        window->draw(botao_fase2);
        window->draw(botao_fase_progresso);
        window->draw(botao_fase_voltar);
    
        sf::Text texto_nome("Seu nome: " + nome_jogador + "_", fonte, 30);
        float largura_texto = texto_nome.getGlobalBounds().width;
        float centro_x = (1024 / 2) - (largura_texto / 2);
        texto_nome.setPosition(centro_x, 150.f); 
        texto_nome.setFillColor(sf::Color::Black);
        window->draw(texto_nome);
    }
    else if (tela == SELECAO_JOGADORES)
    {
        window->draw(fundo_jogadores);
        window->draw(botao_um_jogador);
        window->draw(botao_dois_jogadores);
        window->draw(botao_jogador_voltar);
    }
    else if (tela == PONTUACAO)
    {
        window->draw(fundo_ranking);
        window->draw(botao_ranking_voltar);

        float pos_y = 270.f;
        int posicao_atual = 1;

        // Percore a ordem de ranking
        for (auto it = ordem_ranking.begin(); it != ordem_ranking.end() && posicao_atual <= 8; ++it, posicao_atual++)
        {
            // Coloca o nome do sujeito
            std::string str_exibicao_nome = std::to_string(posicao_atual) + ". " + it->second;
            sf::Text txt_colocado(str_exibicao_nome, fonte, 24);
            txt_colocado.setPosition(264.f, pos_y);
            txt_colocado.setFillColor(sf::Color::Black);
            window->draw(txt_colocado);

            // Coloca a pontuacao
            std::string str_exibicao_pontos = std::to_string(it->first) + " pontos";
            sf::Text txt_pontos(str_exibicao_pontos, fonte, 26);
            txt_pontos.setPosition(670.f, pos_y);
            txt_pontos.setFillColor(sf::Color::Black);
            window->draw(txt_pontos);

            // Pula para escrever o proximo
            pos_y += 25.f;
        }

        if (ordem_ranking.empty())
        {
            sf::Text txt_vazio("Nenhum recorde registrado ainda!", fonte, 24);
            txt_vazio.setPosition(380.f, 250.f);
            txt_vazio.setFillColor(sf::Color(180, 180, 180));
            window->draw(txt_vazio);
        }
    }
    else if (tela == PAUSE)
    {
        window->draw(sprite_fundo_pause);
        window->draw(retangulo_escuro);

        std::string str_pause("JOGO PAUSADO!");
        sf::Text txt_pause(str_pause, fonte, 26);
        txt_pause.setFillColor(sf::Color::White);

        float largura_texto = txt_pause.getGlobalBounds().width;
        float centro_x = (1024 / 2) - (largura_texto / 2);
        txt_pause.setPosition(centro_x, 100);
        window->draw(txt_pause);
        window->draw(botao_pause_continuar);
        window->draw(botao_pause_menu);
    }
}