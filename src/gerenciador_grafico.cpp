#include "gerenciador_grafico.hpp"
#include "ente.hpp"

using namespace gerenciadores;
using namespace std;
using namespace sf;


GerenciadorGrafico::GerenciadorGrafico()
{
    int largura = 640;
    int altura = 480;

    float escala = 1.5;

    window = new sf::RenderWindow(sf::VideoMode(largura * escala, altura * escala), "Jogo Irado");

    View camera (FloatRect(0.f, 0.f, (float)largura, (float)altura));
    window->setView(camera);

    window->setFramerateLimit(60);
}

GerenciadorGrafico::~GerenciadorGrafico()
{
    delete window;
}

void GerenciadorGrafico :: desenharEnte(Ente *pE)
{
    Figura* fig = pE->pFig;

    //muda os frames exibidos
    fig->contador++;
    if (fig->contador >= fig->v_animacao)
    {
        fig->contador = 0;
        fig->frame_atual++;
        if (fig->frame_atual > fig->frame_final)
            fig->frame_atual = fig->frame_inicial;
    }

    //tava servindo ent tinha estado diferente dps arrumo
    /*if (fig->frame_atual < fig->frame_inicial || fig->frame_atual > fig->frame_final)
        fig->frame_atual = fig->frame_inicial;*/

    //recorta o frame
    fig->sprite.setTextureRect(sf::IntRect(fig->frame_atual * fig->frame_largura,
                                            0,
                                            fig->frame_largura,
                                            fig->frame_altura));

    //temporario
    fig->sprite.setPosition(
    pE->getColisao().getPosition().x + fig->offset.x,
    pE->getColisao().getPosition().y + fig->offset.y
    );
    //fig->sprite.setPosition(pE->getColisao().getPosition());

    //window->draw(pE->getColisao());//ate arrumar o sprite
    window->draw(pE->pFig->sprite);  
}
