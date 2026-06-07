#include "lustre.hpp"

using namespace entidades;
using namespace sf;

Lustre::Lustre(int _x, int _y) : Obstaculo(_x, _y)
{
    danoso=true;
    caindo=false;
    //id= ;
    inicializarSprite("assets/lustre.png", 0, 64, 64, 0, 0, 0, sf::Vector2f(0.f, 0.f));

    colisao.setSize(sf::Vector2f(frame_largura, frame_altura));
    colisao.setFillColor(sf::Color::Red);
    colisao.setPosition(x, y);

    area_colisao.setSize(sf::Vector2f(frame_largura, 576));
    area_colisao.setFillColor(sf::Color::Blue);
    area_colisao.setPosition(x, y);
}

Lustre::~Lustre()
{

}

void Lustre::executar()
{
    if(caindo)
    {
        velocidade_y += gravidade;
        y += velocidade_y;
        colisao.setPosition(x, y);
        sprite.setPosition(x, y);
    }
}

void Lustre::obstaculizar(entidades::Jogador* pJog)
{
    FloatRect jog = pJog->getColisao().getGlobalBounds();
    FloatRect area = area_colisao.getGlobalBounds();
    FloatRect lustre = colisao.getGlobalBounds();

    //garante q o jogador esta embaixo e a colisao nao foi apenas lateral
    if (jog.intersects(area) && !caindo) 
    {
        caindo = true;
        area_colisao.setSize({0.f, 0.f});//ativa so uma vez
        return;
    }

    if (caindo && jog.intersects(lustre))
    {
        float dif_altura = jog.top - area.top;
        dano = static_cast<int>(dif_altura * 0.1f);//200 pixels -> 20 de dano
        pJog->receberDano(dano);
        caindo = false;
        velocidade_y = 0.f;
    }
}
