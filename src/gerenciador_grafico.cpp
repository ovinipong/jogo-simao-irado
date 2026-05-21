#include "gerenciador_grafico.hpp"
#include "ente.hpp"

using namespace gerenciadores;
using namespace std;
using namespace sf;


GerenciadorGrafico::GerenciadorGrafico()
{
    obj = new sf::RenderWindow(sf::VideoMode(1280, 720), "Jogo foda");
    obj->setFramerateLimit(60);
}

GerenciadorGrafico::~GerenciadorGrafico()
{
    delete obj;
}

void GerenciadorGrafico :: desenharEnte(Ente *pE)
{
    obj->draw(pE->pFig->sprite);        
}
