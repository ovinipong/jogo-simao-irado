#include "jogador.hpp"

#include <iostream>

using namespace std;
using namespace sf;
using namespace entidades;

#include "projetil.hpp"

// Construtora
Jogador::Jogador(int _x, int _y):
Personagem(_x, _y) 
{
    num_vidas = 40;
    pListaProjeteis = nullptr;
    id =2;
    pontos = 0;
    velocidade_padrao = 4;
    move_speed = velocidade_padrao;
    tempo_efeito = 0.0f;
    tempo_invulneravel= 1.0f;

    inicializarSprite("assets/jogador.png", 17, 64, 128, 8, 2, 9, sf::Vector2f(0.f, -45.f));

    colisao.setSize(sf::Vector2f(50.0f, 50.0f));
    colisao.setFillColor(sf::Color::Green);
}

// Destrutora
Jogador::~Jogador()
{

}

void Jogador :: executar()
{
    x_anterior = x;
    // Verifica se nao esta lento
    if (move_speed < velocidade_padrao)
    {
        if (timer_status.getElapsedTime().asSeconds() >= tempo_efeito)
        {
            move_speed = velocidade_padrao;
        }
    }

    if (timer_status.getElapsedTime().asSeconds()>= tempo_invulneravel)
    {
        invulneravel=false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        x -= move_speed;
        sprite.setScale(-1.f, 1.f);//inverte sprite p esquerda
        sprite.setOrigin(frame_largura, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        x += move_speed;
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(0, 0);
    }

    float gravidade_velocidade = 0.5;
    float pulo_velocidade = -15;

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

    // ATIRAR PEW PEW
    if (Keyboard::isKeyPressed(Keyboard::Z) && timer_atirar.getElapsedTime().asSeconds() >= 0.5)
    {
        atirar();
    }

    no_chao = false;

    y = y + velocidade_y;

    // Atualiza a posicao da colisao (temporario)
    colisao.setPosition((float)x, (float)y);
}

void Jogador :: reverterPosicao()
{
    receberDano(1);
    x=x_anterior;
    colisao.setPosition((float)x, (float)y);
}

void Jogador :: aplicarLentidao(int nova_velocidade, float duracao)
{
    move_speed = nova_velocidade;
    tempo_efeito = duracao;
    timer_status.restart();
}

void Jogador::atirar() 
{
    if (!pListaProjeteis)
    {
        std::cout << "ERRO: O ponteiro da lista esta NULO! O jogador nao tem acesso as balas." << std::endl;
        return;
    }

    // Procura por um projétil inativo na lista
    for (Projetil* proj : *pListaProjeteis) 
    {
        if (!proj->getAtivo() && proj->getTipoProjetil() == JOGADOR) 
        {
            
            bool esquerda = (sprite.getScale().x < 0); 
            
            // Pega a posição do jogador para criar o tiro
            sf::Vector2f pos_tiro = colisao.getPosition();
            
            pos_tiro.y += colisao.getSize().y / 2.0f - 8.0f; // Centraliza na altura
            pos_tiro.x += (esquerda ? -10.f : 50.f);         // Joga um pouco pra frente
            
            // Atira!
            proj->disparar(pos_tiro, esquerda);
            timer_atirar.restart();

            break;
        }
    }
}

void Jogador::operator++()
{
    pontos+=1;
}