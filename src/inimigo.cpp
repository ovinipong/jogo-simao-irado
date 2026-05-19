#include "inimigo.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

Inimigo :: Inimigo (int _x, int _y):
Personagem(_x, _y), nivel_maldade(10)
{
    move_speed = 3;
    velocidade_y = 0.0f;
    no_chao = false;

    sprite.setSize(sf::Vector2f(50.0f, 50.0f));
    sprite.setFillColor(sf::Color::Red);
}

Inimigo :: ~Inimigo()
{

}

void Inimigo :: colidir_bloco(sf::FloatRect *bloco, sf::FloatRect *personagem, sf::FloatRect *interseccao)
{
    // Colisao vertical (eixo Y)
    if (interseccao->height < interseccao->width)
    {
        // Colisao por cima (jogador em cima do bloco)
        if (personagem->top < bloco->top)
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
        if (personagem->left < bloco->left)
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