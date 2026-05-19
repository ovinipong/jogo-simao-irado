#include "jogador.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

// Construtora
Jogador::Jogador(int _x, int _y):
Personagem(_x, _y) 
{
    pontos = 0;
    move_speed = 3;
    velocidade_y = 0;
    no_chao = false;

    sprite.setSize(sf::Vector2f(50.0f, 50.0f));
    sprite.setFillColor(sf::Color::Green);
}

// Destrutora
Jogador::~Jogador()
{

}

void Jogador :: executar()
{
    // Move o player para a direita e para a esquerda
    if (Keyboard::isKeyPressed(Keyboard::Left))
        x = x - (move_speed);
    if (Keyboard::isKeyPressed(Keyboard::Right))
        x = x + (move_speed);

    float gravidade_velocidade = 0.5;
    float pulo_velocidade = -10;

    velocidade_y = velocidade_y + gravidade_velocidade;

    // Pulo
    if (Keyboard::isKeyPressed(Keyboard::Up) && no_chao)
    {
        velocidade_y = pulo_velocidade;
        no_chao = false;
    }

    y = y + velocidade_y;

    // Atualiza a posicao do sprite (temporario)
    sprite.setPosition((float)x, (float)y);
}

void Jogador::desenhar(sf::RenderWindow& window) 
{
    window.draw(sprite);
}

sf::RectangleShape& Jogador :: getSprite()
{
    return sprite;
}

void Jogador :: reverterPosicao()
{
    x=x_anterior;
    sprite.setPosition((float)x, (float)y);
}

void Jogador :: colidir_bloco(sf::FloatRect *bloco, sf::FloatRect *jogador, sf::FloatRect *interseccao)
{
    // Colisao vertical (eixo Y)
    if (interseccao->height < interseccao->width)
    {
        // Colisao por cima (jogador em cima do bloco)
        if (jogador->top < bloco->top)
        {
            y = y - interseccao->height;
            velocidade_y = 0.0f;
            no_chao = true;
        }
        // Colisao por baixo (jogador em baixo do bloco)
        else
        {
            y = y + interseccao->height;
            velocidade_y = 0.0f;
        }
    }
    // Colisao horizontal
    else
    {
        // Colisao pela esquerda (jogador a direita do bloco)
        if (jogador->left < bloco->left)
        {
            x = x - interseccao->width;
        }
        // Colisao pela direita (jogador a esquerda do bloco)
        else
        {
            x = x + interseccao->width;
        }
    }

    sprite.setPosition(x, y);
}

