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
    
}

template <typename TL>
void Lista<TL>::limpar()
{

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
