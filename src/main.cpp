#include "jogo.hpp"

#include <stdlib.h>
#include <time.h>

int main()
{
    
    srand(time(NULL));

    Jogo jogo;

    jogo.executar();


    return 0;
}
