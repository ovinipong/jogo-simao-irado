#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Ente;

namespace gerenciadores{

class GerenciadorGrafico {
    
    private:
        sf::RenderWindow* window;
        sf::View camera;
        sf::Font fonte;
        std::string texto_digitado;
        bool backspace_pressionado;
        bool pausado;

    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE);
        void executar();
        void mostrar();
        void mostrarVida(int vidas1, int vidas2, bool jog2);
        void mostrarPontos(int pontos1, int pontos2, bool jog2);
        void centralizarCamera(sf::Vector2f posicao);
        bool janelaAberta () const
        {
            return window->isOpen();
        }
        sf::RenderWindow* getWindow() 
        { 
            return window; 
        }
        std::string const getTextoDigitado() {return(texto_digitado);}
        bool const getBackspacePressionado() {return(backspace_pressionado);}

        bool getPausado() {return(pausado); }
        void setPausado(bool p) { pausado = p; }
        
        sf::View getCamera();
};

}
