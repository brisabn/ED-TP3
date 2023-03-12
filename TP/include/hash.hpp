#ifndef HASH_HPP
#define HASH_HPP

#include "ListaEncadeada.hpp"

class Hash
{
public:
    Hash(){};

    // Funções Dicionário
    Verbete Pesquisa(Verbete verbete);
    void Insere(Verbete verbete);
    void Atualiza(Verbete verbete, string Atualiza);
    void Remove(Verbete verbete);
    void Destroi();

    void Display(string output);
    void Remove_Verbs();

    static const int M = 52;
    int hash_chave(char chave);
    ListaEncadeada Tabela[M];
};

#endif