#pragma once

#include <SFML/Graphics.hpp>
#include "figura.hpp"
#include "gerenciador_grafico.hpp"

using namespace gerenciadores;

class Ente
{
    protected:
        int id;
        // Gerenciador_grafico *pGG;
        // sf::Sprite *pFigura;
        sf::RectangleShape colisao;
    public:
        Figura* pFig;


    public:
        Ente();
        ~Ente();
        virtual void executar() = 0;
        void desenhar(sf::RenderWindow &window);
        const sf::RectangleShape& getColisao() const;
        // void static setGG(Gerenciador_grafico *GG);

};