#pragma once

#include "ente.hpp"

namespace entidades{

class Entidade : public Ente
{
    protected:
        int x, y;

    public:
        Entidade(int _x, int _y);
        virtual ~Entidade() = 0;
        virtual void executar() = 0;
};

}