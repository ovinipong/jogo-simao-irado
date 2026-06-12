#pragma once

#include "ente.hpp"

namespace entidades{

class Entidade : public Ente
{
    protected:
        int x, y;
        float velocidade_y;
        bool no_chao;
        bool valido;
        static const float gravidade;
        static float dt;//tempo para aplicar gravidade

    public:
        Entidade(int _x=0, int _y=0);
        virtual ~Entidade();
        virtual void executar() = 0;
        sf::Vector2f getXY();
        void setXY(sf::Vector2f position);
        float getVelocidadeY();
        void setVelocidadeY(float vy);
        bool getNoChao();
        void setNoChao(bool n);
        bool getValido() {return valido;};
        void setValido() {valido=true;};
        void setInvalido() {valido=false;};
        static float aplicarGravidade(float velocidade_y, float dt);
    };

}