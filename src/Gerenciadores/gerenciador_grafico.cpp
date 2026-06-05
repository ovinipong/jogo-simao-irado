#include "gerenciador_grafico.hpp"
#include "ente.hpp"

using namespace gerenciadores;
using namespace std;
using namespace sf;


GerenciadorGrafico::GerenciadorGrafico()
{
    int largura = 1024;
    int altura = 576;

    float escala = 1.5;

    window = new sf::RenderWindow(sf::VideoMode(largura * escala, altura * escala), "Jogo Irado");

    camera.setSize((float)largura, (float)altura);
    camera.setCenter((float)largura / 2.f, (float)altura / 2.f);
    window->setView(camera);

    window->setFramerateLimit(60);
}

GerenciadorGrafico::~GerenciadorGrafico()
{
    delete window;
}

void GerenciadorGrafico :: desenharEnte(Ente *pE)
{
    pE->setContador(pE->getContador() + 1);
    if (pE->getContador() >= pE->getVAnimacao())
    {
        pE->setContador(0);
        pE->setFrameAtual(pE->getFrameAtual() + 1);
        if (pE->getFrameAtual() > pE->getFrameFinal())
            pE->setFrameAtual(pE->getFrameInicial());
    }

    pE->getSprite().setTextureRect(sf::IntRect(pE->getFrameAtual() * pE->getFrameLargura(), 0,
                                                pE->getFrameLargura(), pE->getFrameAltura()));

    pE->getSprite().setPosition(
        pE->getColisao().getPosition().x + pE->getOffset().x,
        pE->getColisao().getPosition().y + pE->getOffset().y
    );

    window->draw(pE->getSprite());
}

/*void GerenciadorGrafico :: executar()
{
    while (window->isOpen()) 
    {
        sf::Event event;
        while (window->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window->close();
            }
        }

        window->clear();
        window->display();
    }
}*/

void GerenciadorGrafico::executar()
{
    sf::Event event;
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window->close();

    while (window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
            window->close();
    }

    window->clear();

}

void GerenciadorGrafico::mostrar()
{
    window->display();
}

void GerenciadorGrafico::centralizarCamera(sf::Vector2f posicao)
{
    camera.setCenter(posicao);
    window->setView(camera);
}