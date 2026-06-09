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
        sf::Clock timer_invulneravel;
        bool invulneravel;
        float tempo_invulneravel;
        float tempo_efeito;
        std::vector<Projetil*>*  pListaProjeteis;


    public:
        Jogador(int _x=0, int _y=0);
        ~Jogador();
        void executar();
        void reverterPosicao();
        void aplicarLentidao(int nova_velocidade, float duracao);
        
        void setListaProjeteis(std::vector<Projetil*>* pLista) { pListaProjeteis = pLista; }
        void atirar();
        void operator++();

        int getPontos(){return pontos;};
        int getVida(){return num_vidas;};

        void setInvulneravel(){invulneravel=true;};
        bool getInvulneravel(){return invulneravel;};
};


    enum class EstadoJogador {
        PARADO,
        CORRENDO,
        PULANDO
    };

}