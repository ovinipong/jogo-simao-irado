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

    sprite.setSize(sf::Vector2f(50.0f, 50.0f));
    sprite.setFillColor(sf::Color::Green);
}

// Destrutora
Jogador::~Jogador()
{

}

void Jogador::executar()
{
    x_anterior=x;
    // Move o player para a direita e para a esquerda
    if (Keyboard::isKeyPressed(Keyboard::Left))
        x = x - (move_speed);
    if (Keyboard::isKeyPressed(Keyboard::Right))
        x = x + (move_speed);

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

