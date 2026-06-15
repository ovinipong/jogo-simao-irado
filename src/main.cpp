#include <SFML/Graphics.hpp>
#include "ente.hpp"
#include "jogador.hpp"
#include "bolinho.hpp"
#include "bloco.hpp"
#include "gerenciador_colisoes.hpp"
#include "gerenciador_grafico.hpp"
#include "plataforma.hpp"
#include "jogo.hpp"
#include "fase.hpp"
#include "primeira_fase.hpp"
#include "lista.hpp"
#include "lista_entidades.hpp"

#include <stdlib.h>
#include <time.h>

using namespace entidades;

int main()
{
    /*ids 

    bloco 1
    jogador 2
    inim fácil 3
    inim médio 4 5
    chefão 6
    plataforma 7 8 9
    agua 10
    obst difícil 11
    projetil 12
    fase 1 13
    fase 2 14
    menu 15*/
    
    srand(time(NULL));

    Jogo jogo;

    jogo.executar();


    return 0;
}
