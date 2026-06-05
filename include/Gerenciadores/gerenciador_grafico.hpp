#pragma once

#include <SFML/Graphics.hpp>

class Ente;

namespace gerenciadores{

class GerenciadorGrafico {
    
    private:
        sf::RenderWindow* window;//uml ta obj mas chamaria d pJanela 
        sf::View camera;

    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE);
        void executar();
        void mostrar();
        void centralizarCamera(sf::Vector2f posicao);
        bool janelaAberta () const
        {
            return window->isOpen();
        }
        sf::RenderWindow* getWindow() 
        { 
            return window; 
        }
};

}
