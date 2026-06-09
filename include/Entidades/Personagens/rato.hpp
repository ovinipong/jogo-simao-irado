#pragma once

#include "inimigo.hpp"

namespace entidades
{

class Rato : public Inimigo
{
    private:

    public:
        Rato(int _x=0, int _y=0);
        ~Rato();
        void executar();
        const int get_vida() const; 
        void inverterDirecao();
};

}