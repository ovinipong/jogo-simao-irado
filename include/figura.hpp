#pragma once

//#include <iostream>
#include <SFML/Graphics.hpp>

class Figura
{
    protected:
        sf::Sprite sprite;
        sf::Texture texture;
        int frame_atual;
        int total_frames;       
        int frame_largura;     
        int frame_altura;      
        int contador;          
        int v_animacao;   

        int frame_inicial;
        int frame_final;

        sf::Vector2f offset = {0.f, 0.f};//p ajustar a sprite
    public:
        Figura(const std::string& caminho_imagem)
        {
            texture.loadFromFile(caminho_imagem);
            sprite.setTexture(texture);
        }
        ~Figura()
        {

        }
};
