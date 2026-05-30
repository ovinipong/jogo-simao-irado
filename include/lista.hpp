#pragma once

#include <iostream>

namespace listas{
    
template <typename TL>
class Lista
{
    public:
        template <typename TE>
        class Elemento
        {
            public:
                Elemento<TE>* pProx;
                TE* pInfo;
            public:
                Elemento();
                ~Elemento();
                void incluir(TE* p);
                void setProx(Elemento<TE>* pE)
                {
                    pProx=pE;
                }
                const Elemento<TE>* getProx() const
                {
                    return pProx;
                }
        };

    private:
        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;
    public:
        Lista();
        ~Lista();
        void incluir(TL* p);
        void limpar();
        void remover(TL* p);
        const Elemento<TL>* getPrimeiro() const
        {
            return pPrimeiro;
        }
        const Elemento<TL>* getUltimo() const
        {
            return pUltimo;
        }
};

template <typename TL>
Lista<TL>::Lista() : pPrimeiro(NULL), pUltimo(NULL)
{

}

template <typename TL>
Lista<TL>::~Lista()
{
    limpar();
    pPrimeiro=NULL;
    pUltimo=NULL;
}

template <typename TL>
void Lista<TL>::incluir(TL* p)
{
     if (p == NULL) return;

    Elemento<TL>* novo = new Elemento<TL>();
    novo->incluir(p);
    novo->pProx = pPrimeiro;
    pPrimeiro = novo;

    if (pUltimo == NULL)
    {
        pUltimo = novo;
    }
}

template <typename TL>
void Lista<TL>::limpar()
{
    while(pPrimeiro != NULL)
    {
        Elemento<TL>* aux = pPrimeiro;
        pPrimeiro = pPrimeiro->pProx;
        delete(aux);
    }
    pUltimo = NULL;
}

template <typename TL>
void Lista<TL>::remover(TL* p)
{
    Elemento<TL>* ant = NULL;
    Elemento<TL>* aux = pPrimeiro;

    while (aux != NULL)
    {
        if (aux->pInfo == p)
        {
            if (ant == NULL)
                pPrimeiro = aux->pProx;
            else
                ant->pProx = aux->pProx;

            if (aux == pUltimo)
                pUltimo = ant;

            delete aux;
            return;
        }
        ant = aux;
        aux = aux->pProx;
    }
}

template <typename TL>
template <typename TE>
Lista<TL> :: Elemento<TE> :: Elemento() : pProx(NULL), pInfo(NULL)
{

}

template <typename TL>
template <typename TE>
Lista<TL> :: Elemento<TE> :: ~Elemento()
{
    pProx=NULL;
    pInfo=NULL;
}

template <typename TL>
template <typename TE>
void Lista<TL> :: Elemento<TE> :: incluir(TE* p)
{
    pInfo=p;
}

}
