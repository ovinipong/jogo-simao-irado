#pragma once

#include "inimigo.hpp"

namespace entidades
{

enum EstadoBolo
{
    PARADO, PULANDO
};

class Bolo : public Inimigo
{
    private:
        int velocidade_x;
        EstadoBolo estado;
        sf::Clock timer_pular;
        float tempo_parado;
        float pulo_velocidade;
        
    public:
        Bolo(int _x=0, int _y=0);
        ~Bolo();
        void executar();
        const int get_vida() const; 
        void inverterDirecao();
};

}