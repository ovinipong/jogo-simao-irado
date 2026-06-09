#pragma once

#include "inimigo.hpp"

namespace entidades
{

class Rato : public Inimigo
{
    private:

    public:
        Rato(int _x, int _y);
        ~Rato();
        void executar();
        const int get_vida() const; 
        void inverterDirecao();
};

}