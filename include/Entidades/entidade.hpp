#pragma once

#include "ente.hpp"

namespace entidades{

class Entidade : public Ente
{
    protected:
        int x, y;
        float velocidade_y;
        bool no_chao;
        static const float gravidade;

    public:
        Entidade(int _x, int _y);
        virtual ~Entidade();
        virtual void executar() = 0;
        sf::Vector2f getXY();
        void setXY(sf::Vector2f position);
        float getVelocidadeY();
        void setVelocidadeY(float vy);
        bool getNoChao();
        void setNoChao(bool n);
};

}