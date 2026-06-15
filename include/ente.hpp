#pragma once

#include <SFML/Graphics.hpp>
#include "figura.hpp"
#include "gerenciador_grafico.hpp"

using namespace gerenciadores;

class Ente : public Figura
{
    protected:
        int id;
        static GerenciadorGrafico* pGG;
        sf::Sprite* pFigura;
        sf::RectangleShape colisao;

    public:
        Ente();
        ~Ente();
        virtual void executar() = 0;
        //void desenhar(sf::RenderWindow &window);
        void desenhar();
        const sf::RectangleShape& getColisao() const;
        static void setGG(GerenciadorGrafico *pG);
        static GerenciadorGrafico* getGG();
        int getID() {return id;};
};