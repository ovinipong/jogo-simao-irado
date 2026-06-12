#include "entidade.hpp"
#include "gerenciador_colisoes.hpp"

using namespace std;
using namespace sf;
using namespace entidades;

const float Entidade::gravidade = 0.98f;
float Entidade::dt = 1.0f;
float Entidade::aplicarGravidade(float velocidade_y, float dt)
{
    return velocidade_y +=  gravidade * dt;
}

Entidade::Entidade(int _x, int _y)
{
    // Atribui as posicoes iniciais
    x = _x;
    y = _y;

    colisao.setPosition(x, y);

    velocidade_y = 0;
    no_chao = false;
}

Entidade::~Entidade()
{
    
}

Vector2f Entidade::getXY()
{
    Vector2f position(x, y);
    return(position);
}

void Entidade::setXY(Vector2f position)
{
    x = position.x;
    y = position.y;
    colisao.setPosition(position);
}

float Entidade::getVelocidadeY()
{
    return(velocidade_y);
}

void Entidade::setVelocidadeY(float vy)
{
    velocidade_y = vy;
}

bool Entidade::getNoChao()
{
    return(no_chao);
}

void Entidade::setNoChao(bool n)
{
    no_chao = n;
}
