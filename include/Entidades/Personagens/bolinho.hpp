#pragma once

#include "inimigo.hpp"

namespace entidades {

class Bolinho : public Inimigo
{
    private:
        int reducao_velocidade; 
        int move_speed;
        float tempo;
        
    public:
        Bolinho(int _x=0, int _y=0);
        ~Bolinho();
        void executar();
        void danificar(Jogador* p); 
        void inverterDirecao();
        void salvar(std::ofstream& arquivo);
        void setMoveSpeed(int mp) { move_speed = mp; };
};

}