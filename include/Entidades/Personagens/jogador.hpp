#pragma once

#include "personagem.hpp"

class Projetil;

namespace entidades {

class Jogador : public Personagem
{
    private:
        int pontos;
        int move_speed;
        int velocidade_padrao;
        int x_anterior;
        float pulo_velocidade;
        sf::Clock timer_status;
        sf::Clock timer_atirar;
        sf::Clock timer_invulneravel;
        bool invulneravel;
        float tempo_invulneravel;
        float tempo_efeito;
        std::vector<Projetil*>*  pListaProjeteis;
        bool segundo;


    public:
        Jogador(int _x=0, int _y=0, bool segundo_jog=false);
        ~Jogador();
        void executar();
        void reverterPosicao();
        void aplicarLentidao(int nova_velocidade, float duracao);
        
        void setListaProjeteis(std::vector<Projetil*>* pLista) { pListaProjeteis = pLista; }
        void atirar(bool projJog1);
        void operator++();

        int getPontos(){return pontos;};
        void setPontos(int p) {pontos = p;};
        int getVida(){return num_vidas;};

        void setInvulneravel(){invulneravel=true;};
        bool getInvulneravel(){return invulneravel;};

        bool getSegundo(){return segundo;};
};


    enum class EstadoJogador {
        PARADO,
        CORRENDO,
        PULANDO
    };

}