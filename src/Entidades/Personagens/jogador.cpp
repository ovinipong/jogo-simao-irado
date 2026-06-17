#include "jogador.hpp"

#include <iostream>

using namespace std;
using namespace sf;
using namespace entidades;

#include "projetil.hpp"

// Construtora
Jogador::Jogador(int _x, int _y, bool segundo_jog):
Personagem(_x, _y) 
{
    num_vidas = 40;
    pListaProjeteis = nullptr;
    id =2;
    segundo = segundo_jog;
    pontos = 0;
    velocidade_padrao = 4;
    move_speed = velocidade_padrao;
    tempo_efeito = 0.0f;
    tempo_invulneravel= 1.0f;
    pulo_velocidade = -20.0f;

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
        if (timer_lentidao.getElapsedTime().asSeconds()>= tempo_efeito)
        {
            move_speed = velocidade_padrao;
        }
    }

    if (timer_invulneravel.getElapsedTime().asSeconds()>= tempo_invulneravel)
    {
        invulneravel=false;
        timer_invulneravel.restart();
    }

    if (!segundo)
    {
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            x -= move_speed;
            sprite.setScale(-1.f, 1.f);//inverte sprite p esquerda
            sprite.setOrigin(frame_largura, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            x += move_speed;
            sprite.setScale(1.f, 1.f);
            sprite.setOrigin(0, 0);
        }
            // Pulo
        if (Keyboard::isKeyPressed(Keyboard::W) && (getNoChao()==true))
        {
            velocidade_y = pulo_velocidade;
            setNoChao(false);
        }
        // Se estiver no ar mas nao estiver apertando a tecla de pular, ele vai fazer cair
        if (!Keyboard::isKeyPressed(Keyboard::W) && velocidade_y < 0.0f)
        {
            velocidade_y = velocidade_y * 0.8f; 
        }

        // ATIRAR PEW PEW
        if (Keyboard::isKeyPressed(Keyboard::LShift) && timer_atirar.getElapsedTime().asSeconds() >= 0.5)
        {
            atirar(true);
        }

    }
    else //é o segundo player
    {
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
            // Pulo
        if (Keyboard::isKeyPressed(Keyboard::Up) && (getNoChao()==true))
        {
            velocidade_y = pulo_velocidade;
            setNoChao(false);
        }
        // Se estiver no ar mas nao estiver apertando a tecla de pular, ele vai fazer cair
        if (!Keyboard::isKeyPressed(Keyboard::Up) && velocidade_y < 0.0f)
        {
            velocidade_y = velocidade_y * 0.8f; 
        }

        // ATIRAR PEW PEW
        if (Keyboard::isKeyPressed(Keyboard::M) && timer_atirar.getElapsedTime().asSeconds() >= 0.5)
        {
            atirar(false);
        }
    }
    
    if (getNoChao()==true)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = aplicarGravidade(velocidade_y, dt);
    }                           

    setNoChao(false);

    y += velocidade_y * dt;

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
    timer_lentidao.restart();
}

void Jogador::atirar(bool projJog1) 
{
    if (!pListaProjeteis)
    {
        return;
    }

    // Procura por um projétil inativo na lista
    for (Projetil* proj : *pListaProjeteis) 
    {
        if (!proj->getAtivo() && proj->getTipoProjetil() == JOGADOR) 
        {
            if (projJog1==true)
            {
                proj->setOrigemProj(projJog1); //projetil do jogador 1
            }
            
            bool esquerda = (sprite.getScale().x < 0); 
            
            // Pega a posição do jogador para criar o tiro
            sf::Vector2f pos_tiro = colisao.getPosition();
            
            pos_tiro.y += colisao.getSize().y / 2.0f - 8.0f;
            
            if (esquerda) pos_tiro.x += -10.f;
            else pos_tiro.x += 50.f;
            
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