#include "hash.hpp"

// Calcula a chave hash
int Hash::hash_chave(char chave)
{
    // é baseado no valor ASCII da primera letra

    erroAssert(chave <= 90 || chave >= 97, "O primeiro caracter não é uma letra");

    if (chave <= 90)
        chave = chave - 65;
    else
        chave = chave - 97 + 26;
    return int(chave);
}

// Pesquisa pelo verbete na lista encadeada do seu número hash
Verbete Hash::Pesquisa(Verbete verb)
{
    int pos = hash_chave(verb.chave);
    avisoAssert(pos <= 52 && pos >= 0, "A posição não é válida");
    return Tabela[pos].Pesquisa(verb);
}

// Insere o verbete na lista encadeada do seu número hash
void Hash::Insere(Verbete verb)
{
    int pos = hash_chave(verb.chave);
    avisoAssert(pos <= 52 && pos >= 0, "A posição não é válida");
    Tabela[pos].InsereItem(verb);
}

// Atualiza o verbete na lista encadeada do seu número hash
void Hash::Atualiza(Verbete verbete, string s)
{
    int pos = hash_chave(verbete.chave);
    avisoAssert(pos <= 52 && pos >= 0, "A posição não é válida");
    Tabela[pos].Replace(verbete, s);
}

// Remove o verbete da lista encadeada do seu número hash
void Hash::Remove(Verbete verb)
{
    int pos = hash_chave(verb.chave);
    avisoAssert(pos <= 52 && pos >= 0, "A posição não é válida");
    Tabela[pos].RemoveItem(verb);
}

// Imprime em ordem, já que os verbetes foram inseridos em ordem nas listas encadeadas
void Hash::Display(string output)
{
    for (int i = 0; i < M; i++)
    {
        Tabela[i].Imprime(output);
    }
}

void Hash::Remove_Verbs()
{
    for (int i = 0; i < M; i++)
    {
        Verbete verb;
        Tabela[i].VerbetesVazios();
    }
}

void Hash::Destroi()
{
    for (int i = 0; i < M; i++)
    {
        Tabela[i].Limpa();
    }
}