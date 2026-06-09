#pragma once

#include <SFML/Graphics.hpp>

class Ente;

namespace gerenciadores{

class GerenciadorGrafico {
    
    private:
        sf::RenderWindow* window;//uml ta obj mas chamaria d pJanela 
        sf::View camera;

        sf::Font fonte;

    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE);
        void executar();
        void mostrar();
        void mostrarVida(int vidas);
        void mostrarPontos(int pontos);
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
