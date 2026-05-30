#include <SFML/Graphics.hpp>
#include "ente.hpp"
#include "jogador.hpp"
#include "inimigo_facil.hpp"
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
    srand(time(NULL));

    Jogo jogo;

    jogo.executar();


    return 0;
}
