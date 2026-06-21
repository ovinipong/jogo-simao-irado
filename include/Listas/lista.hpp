#pragma once

#include <iostream>

namespace listas {
    
template <typename TL>
class Lista
{
    public:
        template <typename TE>
        class Elemento
        {
            private:
                Elemento<TE>* pProx;
                TE* pInfo;
                
            public:
                Elemento();
                ~Elemento();
                
                void setInfo(TE* p)
                {
                    pInfo = p;
                }
                
                TE* getInfo() const
                {
                    return pInfo;
                }

                void setProx(Elemento<TE>* pE)
                {
                    pProx = pE;
                }
                
                Elemento<TE>* getProx()
                {
                    return pProx;
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
        
        Elemento<TL>* getPrimeiro()
        {
            return pPrimeiro;
        }
        
        const Elemento<TL>* getPrimeiro() const
        {
            return pPrimeiro;
        }
        
        Elemento<TL>* getUltimo()
        {
            return pUltimo;
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
    pPrimeiro = NULL;
    pUltimo = NULL;
}

template <typename TL>
void Lista<TL>::incluir(TL* p)
{
    if (p == NULL) return;

    Elemento<TL>* novo = new Elemento<TL>();
    novo->setInfo(p);
    novo->setProx(NULL);

    if (pUltimo == NULL)
    {
        pPrimeiro = novo;
        pUltimo = novo;
    }
    else
    {
        pUltimo->setProx(novo);
        pUltimo = novo;
    }
}

template <typename TL>
void Lista<TL>::limpar()
{
    while(pPrimeiro != NULL)
    {
        Elemento<TL>* aux = pPrimeiro;
        pPrimeiro = pPrimeiro->getProx();
        delete aux->getInfo();
        delete aux;
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
        if (aux->getInfo() == p)
        {
            if (ant == NULL)
                pPrimeiro = aux->getProx();
            else
                ant->setProx(aux->getProx());

            if (aux == pUltimo)
                pUltimo = ant;

            delete aux->getInfo();
            delete aux;
            return;
        }
        ant = aux;
        aux = aux->getProx();
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
    pProx = NULL;
    pInfo = NULL;
}

}

