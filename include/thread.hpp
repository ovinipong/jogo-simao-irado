#pragma once

#include <pthread.h>

//Implementação de threads do POSIX (pthreads) e uso de mutex
//Classe abstrata para a classe Rato

class Thread
{
    protected:
        pthread_t thread_id;   //cada thread recebe um id único
        pthread_mutex_t mutex; //lock e unlock
                               //protege trechos de código do acesso simultâneo de múltiplas threads
        bool executando;       //controla se o laço dentro de executarThread deve continuar executando

    public:
        Thread();
        virtual ~Thread();

        // método que vai rodar dentro da thread (cada classe filha implementa o seu)
        virtual void* executarThread() = 0;

        void iniciarThread();   // pthread_create, começa a executar a thread em paralelo
        void pararThread();     // pthread_join

        // estes métodos são chamados toda vez que a classe for interagir com uma variável compartilhada entre threads
        void lock();
        void unlock();

        bool getExecutando() { return executando; }

    private:
        static void* threadFunc(void* arg);  
};