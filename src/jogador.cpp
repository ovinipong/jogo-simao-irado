#include "jogador.hpp"

#include "bloco.hpp"

using namespace std;
using namespace sf;

// Construtora
Jogador::Jogador(int _x, int _y):
Personagem(_x, _y) 
{
    pontos = 0;
    move_speed = 3;

    velocidade_y = 0.0f;
    no_chao = false;

    colisao.setSize(sf::Vector2f(50.0f, 50.0f));
    colisao.setFillColor(sf::Color::Green);
}

// Destrutora
Jogador::~Jogador()
{

}

void Jogador::executar()
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
    colisao.setPosition((float)x, (float)y);
}

void Jogador::desenhar(sf::RenderWindow& window) 
{
    window.draw(colisao);
}

bool Jogador::aabb(RectangleShape r)
{
    RectangleShape a = colisao;

    // Se tiver colidindo, retorna true
    if (a.getGlobalBounds().intersects(r.getGlobalBounds()))
    {
        return(true);
    }
    // Caso contrario, falso
    else
    {
        return(false);
    }

}

void Jogador::colisao_bloco(Bloco *b)
{
    FloatRect jogador_colisao = colisao.getGlobalBounds();
    FloatRect bloco_colisao = b->get_colisao().getGlobalBounds();
    FloatRect interseccao;

    // Se colidir com o bloco
    if (jogador_colisao.intersects(bloco_colisao, interseccao))
    {
        // Colisao vertical
        if (interseccao.height < interseccao.width)
        {
            // Colisao por cima
            if (jogador_colisao.top < bloco_colisao.top)
            {
                y = y - interseccao.height;
                velocidade_y = 0.0f;
                no_chao = true;
            }
        }

        colisao.setPosition((float)y, (float)x);
    }
}