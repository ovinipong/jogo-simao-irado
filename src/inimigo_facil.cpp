#include "inimigo_facil.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

InimigoFacil :: InimigoFacil(int _x, int _y): Inimigo(_x, _y)
{
    id =3;
    dano=nivel_maldade*1;
    velocidade_y = 0;
    pFig = new Figura ("assets/inimigo.png");

    pFig->frame_atual= 0;
    pFig->total_frames= 2;
    pFig->frame_largura= 64;
    pFig->frame_altura= 64;
    pFig->contador= 0;
    pFig->v_animacao= 8;

    pFig->sprite.setTextureRect(sf::IntRect(0, 0, pFig->frame_largura, pFig->frame_altura));
    pFig->offset = {0.f, 3.f};//ajustar sprite

    colisao.setSize(sf::Vector2f(50.0f, 50.0f));
    colisao.setFillColor(sf::Color::Red);
}

InimigoFacil :: ~InimigoFacil()
{

}

void InimigoFacil :: executar()
{
    pFig->frame_inicial = 0;
    pFig->frame_final = 1;
    x = x + move_speed;


    float gravidade_velocidade = 0.5;
    
    if (no_chao)
    {
        velocidade_y = 0.0f;
    }
    else
    {
        velocidade_y = velocidade_y + gravidade_velocidade;
    }

    no_chao = false;
    
    y = y + velocidade_y;    

    colisao.setPosition((float)x, (float)y);
}

const int InimigoFacil :: get_vida() const
{
    return vida;
}

void InimigoFacil :: inverterDirecao()
{
    move_speed = -move_speed;
}