#pragma once

#include <SFML/Graphics.hpp>

//class Gerenciador_grafico;

class Ente
{
    protected:
        int id;
        // Gerenciador_grafico *pGG;
        // sf::Sprite *pFigura;
        sf::RectangleShape colisao;

    public:
        Ente();
        ~Ente();
        virtual void executar() = 0;
        void desenhar(sf::RenderWindow &window);
        sf::RectangleShape getColisao();
        // void static setGG(Gerenciador_grafico *GG);

};