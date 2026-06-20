#include "thread.hpp"

Thread::Thread() : executando(false)
{
    pthread_mutex_init(&mutex, NULL);
}

Thread::~Thread()
{
    pararThread();
    pthread_mutex_destroy(&mutex);
}

// pthread_create só aceita função estática/C-style
// é um método intermediário à pthread_create
void* Thread::threadFunc(void* arg)
{
    Thread* self = static_cast<Thread*>(arg);
    return self->executarThread();
}

void Thread::iniciarThread()
{
    executando = true;
    pthread_create(&thread_id, NULL, &Thread::threadFunc, this);
}

void Thread::pararThread()
{
    if (executando)
    {
        executando = false;
        pthread_join(thread_id, NULL);
    }
}

void Thread::lock()   
{
    pthread_mutex_lock(&mutex); 
}

void Thread::unlock() 
{
    pthread_mutex_unlock(&mutex); 
}