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

    pausado = false;
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
    texto_digitado = "";
    backspace_pressionado = false;

    while (window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
            window->close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window->close();

        // Verifica se apertou para inserir um texto
        if (event.type == sf::Event::TextEntered)
        {
            // Verifica se nao apertou backspace
            if (event.text.unicode == '\b')
            {
                backspace_pressionado = true;
            }
            else if (event.text.unicode < 128 && event.text.unicode > 31)
            {
                texto_digitado += static_cast<char>(event.text.unicode);
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::P)
            {
                pausado = !pausado;
            }
        }
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

void GerenciadorGrafico::mostrarVida(int vidas1, int vidas2, bool jog2)
{
    //by claude para poder testar as vidas do player melhor
    sf::View view_jogo = window->getView();
    window->setView(window->getDefaultView());

    sf::Text t1;
    t1.setFont(fonte);
    t1.setString("Vidas: " + std::to_string(vidas1));
    t1.setCharacterSize(20);
    t1.setFillColor(sf::Color::White);
    t1.setOutlineColor(sf::Color::Black);
    t1.setOutlineThickness(2.f);
    t1.setPosition(16.f, 16.f);
    window->draw(t1);

    if (jog2)
    {
        sf::Text t2;
        t2.setFont(fonte);
        t2.setString("Vidas: " + std::to_string(vidas2));
        t2.setCharacterSize(20);
        t2.setFillColor(sf::Color::White);
        t2.setOutlineColor(sf::Color::Black);
        t2.setOutlineThickness(2.f);
        t2.setPosition(1306.f, 16.f);
        window->draw(t2);
    }

    window->setView(view_jogo);
}

void GerenciadorGrafico::mostrarPontos(int pontos1, int pontos2, bool jog2)
{
    //by claude para poder testar as vidas do player melhor
    sf::View view_jogo = window->getView();
    window->setView(window->getDefaultView());

    sf::Text t1;
    t1.setFont(fonte);
    t1.setString("Pontos: " + std::to_string(pontos1));
    t1.setCharacterSize(20);
    t1.setFillColor(sf::Color::White);
    t1.setOutlineColor(sf::Color::Black);
    t1.setOutlineThickness(2.f);
    t1.setPosition(160.f, 16.f);
    window->draw(t1);

    if (jog2)
    {
        sf::Text t2;
        t2.setFont(fonte);
        t2.setString("Pontos: " + std::to_string(pontos2));
        t2.setCharacterSize(20);
        t2.setFillColor(sf::Color::White);
        t2.setOutlineColor(sf::Color::Black);
        t2.setOutlineThickness(2.f);
        t2.setPosition(1450.f, 16.f);
        window->draw(t2);    
    }

    window->setView(view_jogo);
}

sf::View GerenciadorGrafico :: getCamera()
{
    return(camera);
}

