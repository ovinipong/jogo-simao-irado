#include "lustre.hpp"

using namespace entidades;
using namespace sf;

Lustre::Lustre(int _x, int _y) : Obstaculo(_x, _y)
{
    danoso=true;
    //id= ;
    inicializarSprite("assets/lustre.png", 0, 64, 64, 0, 0, 0, sf::Vector2f(0.f, 0.f));

    colisao.setSize(sf::Vector2f(frame_largura, 576));
    colisao.setFillColor(sf::Color::Red);
    colisao.setPosition(x, y);
}

Lustre::~Lustre()
{

}

void Lustre::executar()
{

}

void Lustre::obstaculizar(entidades::Jogador* pJog)
{
    FloatRect jogador_colisao = pJog->getColisao().getGlobalBounds();
    FloatRect lustre_colisao  = this->getColisao().getGlobalBounds();

    if (jogador_colisao.top > lustre_colisao.top)
    {
        float diferenca_altura = pJog->getColisao().getPosition().y - y;
        dano = (int)(diferenca_altura * 0.1f);
        if (dano < 0) 
            dano = 0;

        pJog->receberDano(dano);
    }
}
