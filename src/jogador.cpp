#include "jogador.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

// Construtora
Jogador::Jogador(int _x, int _y):
Personagem(_x, _y) 
{
    pontos = 0;
    velocidade_padrao = 4;
    move_speed = velocidade_padrao;
    tempo_efeito = 0.0f;

    pFig = new Figura("assets/jogador.png");

    pFig->frame_atual= 0;
    pFig->total_frames= 17;   
    pFig->frame_largura=64;
    pFig->frame_altura=128;  
    pFig->contador= 0;
    pFig->v_animacao= 8;// troca de frame a cada 8 ticks

    //primeiro ta sendo definido aqui
    pFig->sprite.setTextureRect(sf::IntRect(0, 0, pFig->frame_largura, pFig->frame_altura));
    pFig->offset = {0.f, -45.f};//ajustar sprite

    colisao.setSize(sf::Vector2f(50.0f, 50.0f));
    colisao.setFillColor(sf::Color::Green);
}

// Destrutora
Jogador::~Jogador()
{
    delete pFig;
}

void Jogador :: executar()
{
    // Verifica se nao esta lento
    if (move_speed < velocidade_padrao)
    {
        if (timer_status.getElapsedTime().asSeconds() >= tempo_efeito)
        {
            move_speed = velocidade_padrao;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        x -= move_speed;
        pFig->sprite.setScale(-1.f, 1.f);//inverte sprite p esquerda
        pFig->sprite.setOrigin(pFig->frame_largura, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        x += move_speed;
        pFig->sprite.setScale(1.f, 1.f);
        pFig->sprite.setOrigin(0, 0);
    }

    float gravidade_velocidade = 0.5;
    float pulo_velocidade = -12;

    if (no_chao)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = velocidade_y + gravidade_velocidade;
    }

    // Pulo
    if (Keyboard::isKeyPressed(Keyboard::Up) && no_chao)
    {
        velocidade_y = pulo_velocidade;
        no_chao = false;
    }
    // Se estiver no ar mas nao estiver apertando a tecla de pular, ele vai fazer cair
    if (!Keyboard::isKeyPressed(Keyboard::Up) && velocidade_y < 0.0f)
    {
        velocidade_y = velocidade_y * 0.8f; 
    }

    pFig->frame_inicial = 2;   //so corre
    pFig->frame_final   = 9;

    no_chao = false;

    y = y + velocidade_y;

    // Atualiza a posicao da colisao (temporario)
    colisao.setPosition((float)x, (float)y);
}

void Jogador :: reverterPosicao()
{
    x=x_anterior;
    colisao.setPosition((float)x, (float)y);
}

void Jogador :: aplicarLentidao(int nova_velocidade, float duracao)
{
    move_speed = nova_velocidade;
    tempo_efeito = duracao;
    timer_status.restart();
}