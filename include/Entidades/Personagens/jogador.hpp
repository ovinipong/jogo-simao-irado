#pragma once

#include "personagem.hpp"

class Projetil;

namespace entidades {

class Jogador : public Personagem
{
    protected:
        int pontos;
        int move_speed;
        int velocidade_padrao;
        int x_anterior;
        sf::Clock timer_status;
        sf::Clock timer_atirar;
        float tempo_efeito;
        std::vector<Projetil*>*  pListaProjeteis;


    public:
        Jogador(int _x, int _y);
        ~Jogador();
        void executar();
        void reverterPosicao();
        void aplicarLentidao(int nova_velocidade, float duracao);
        void receberDano(int dano);
        
        void setListaProjeteis(std::vector<Projetil*>* pLista) { pListaProjeteis = pLista; }
        void atirar();

        int getVida(){return num_vidas;};
};


    enum class EstadoJogador {
        PARADO,
        CORRENDO,
        PULANDO
    };

}