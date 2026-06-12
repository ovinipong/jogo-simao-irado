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

    fonte.loadFromFile("assets/m6x11.ttf");
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

void GerenciadorGrafico::mostrarVida(int vidas)
{
    //by claude para poder testar as vidas do player melhor
    sf::View view_jogo = window->getView();
    window->setView(window->getDefaultView());

    sf::Text t;
    t.setFont(fonte);
    t.setString("Vidas: " + std::to_string(vidas));
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::White);
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(2.f);
    t.setPosition(16.f, 16.f);
    window->draw(t);

    window->setView(view_jogo);
}

void GerenciadorGrafico::mostrarPontos(int pontos)
{
    //by claude para poder testar as vidas do player melhor
    sf::View view_jogo = window->getView();
    window->setView(window->getDefaultView());

    sf::Text t;
    t.setFont(fonte);
    t.setString("Pontos: " + std::to_string(pontos));
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::White);
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(2.f);
    t.setPosition(160.f, 16.f);
    window->draw(t);

    window->setView(view_jogo);
}

sf::View GerenciadorGrafico :: getCamera()
{
    return(camera);
}

