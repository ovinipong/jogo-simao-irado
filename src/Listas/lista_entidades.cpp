#include "lista_entidades.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace listas;

ListaEntidades :: ListaEntidades() : LEs()
{
    
}

ListaEntidades :: ~ListaEntidades()
{
    
}

void ListaEntidades :: incluir(Entidade* pE)
{
    LEs.incluir(pE);  
}

void ListaEntidades :: percorrer()
{
    auto aux = LEs.getPrimeiro();
    while (aux != NULL)
    {
        if (aux->getInfo() != NULL)
        {
            aux->getInfo()->executar();
        }
        aux = aux->getProx();
    }
}

void ListaEntidades :: percorrer_remover()
{
    auto aux = LEs.getPrimeiro();
    while (aux != NULL)
    {
        auto aux2 = aux->getProx(); // arrumar lista
        if(aux->getInfo()->getValido() == false)
        {
            LEs.remover(aux->getInfo());
        }
        aux = aux2;
    }
}

void ListaEntidades :: percorrer_desenhar()
{
    auto aux = LEs.getPrimeiro();
    
    while (aux != NULL)
    {
        if (aux->getInfo() != NULL)
        {
            aux->getInfo()->desenhar();
        }
        aux = aux->getProx();
    }
}

void ListaEntidades :: remover(Entidade* pE)
{
    LEs.remover(pE);
}

void ListaEntidades :: limpar()
{
    LEs.limpar();
}

void ListaEntidades :: percorrerSalvar()
{
    // Abre o arquivo e ja limpa o que estava escrito la
    std::ofstream arquivo("assets/salvar/salvar_fase.txt", std::ios::out | std::ios::trunc);

    // Se nao conseguir abrir o arquivo, imprime a mensagem de erro e sai
    if (!arquivo.is_open())
    {
        std::cerr << "Nao foi possivel abrir o salvar_fase.txt" << std::endl;
        return;
    }

    // Vai percorrer a lista
    auto aux = LEs.getPrimeiro();
    while(aux != NULL)
    {
        if (aux->getInfo()->getID() != 1)
        {
            aux->getInfo()->salvar(arquivo);
        }

        aux = aux->getProx();
    }

    arquivo.close();
}