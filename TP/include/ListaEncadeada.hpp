#ifndef LISTA_HPP
#define LISTA_HPP

#include "significados.hpp"

using namespace std;

class Celula_Verbete
{
public:
    Celula_Verbete()
    {
        verbete.chave = ' ';
        verbete.palavra = " ";
        prox = NULL;
    }

public:
    Verbete verbete;
    Celula_Verbete *prox;
    friend class ListaEncadeada;
};

class ListaEncadeada
{
public:
    int tamanho;
    ListaEncadeada();
    int GetTamanho() { return tamanho; };
    bool Vazio() { return tamanho == 0; };

    ~ListaEncadeada();

    void SetItem(Verbete verbete, int pos);
    void Replace(Verbete verbete, string a);
    void InsereItem(Verbete verbete);
    Verbete RemoveItem(Verbete verbete);
    Verbete Pesquisa(Verbete c);
    void Imprime(string output);
    void Limpa();
    void VerbetesVazios();

public:
    Celula_Verbete *primeiro;
    Celula_Verbete *ultimo;
    Celula_Verbete *Posiciona(int pos, bool antes);
};

#endif