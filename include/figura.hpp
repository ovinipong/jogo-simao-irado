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
        sf::Vector2f offset;//p ajustar a sprite
        
    public:
        Figura():frame_atual(0), total_frames(1), frame_largura(0), frame_altura(0),
                contador(0), v_animacao(0), frame_inicial(0), frame_final(0),
                offset(sf::Vector2f(0.f, 0.f))
        {

        }
        ~Figura()
        {

        }
        void inicializarSprite(const std::string& caminho, int totalFrames, 
                                int fLargura, int fAltura, int vAnimacao,
                                int fInicial, int fFinal, sf::Vector2f off = sf::Vector2f(0.f, 0.f))
        {
            texture.loadFromFile(caminho);
            sprite.setTexture(texture);
            frame_atual    = 0;
            total_frames   = totalFrames;
            frame_largura  = fLargura;
            frame_altura   = fAltura;
            contador       = 0;
            v_animacao     = vAnimacao;
            frame_inicial  = fInicial;
            frame_final    = fFinal;
            offset         = off;
            sprite.setTextureRect(sf::IntRect(0, 0, frame_largura, frame_altura));
        }
        sf::Sprite& getSprite()           { return sprite; }
        sf::Vector2f getOffset() const    { return offset; }
        int getFrameAtual() const         { return frame_atual; }
        int getFrameLargura() const       { return frame_largura; }
        int getFrameAltura() const        { return frame_altura; }
        int getFrameInicial() const       { return frame_inicial; }
        int getFrameFinal() const         { return frame_final; }
        int getContador() const           { return contador; }
        int getVAnimacao() const          { return v_animacao; }
        void setFrameAtual(int f)         { frame_atual = f; }
        void setContador(int c)           { contador = c; }
};
