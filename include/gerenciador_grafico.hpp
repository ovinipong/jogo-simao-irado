#pragma once

#include <SFML/Graphics.hpp>

class Ente;

namespace gerenciadores{

class GerenciadorGrafico {
    
    public:
        sf::RenderWindow* window;//uml ta obj mas chamaria d pJanela 
    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE);

};

}
