#ifndef SIGNIFICADOS_HPP
#define SIGNIFICADOS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "msgassert.hpp"

using namespace std;

class Frase
{
public:
    string sig;
    Frase *next;

    Frase()
    {
        sig = " ";
        next = NULL;
    }
    Frase(string sig)
    {
        this->sig = sig;
        this->next = NULL;
    }
};

class ListaFrases
{
public:
    Frase *head;

    ListaFrases()
    {
        head = NULL;
    }

    void adicionar_sig(string sig)
    {
        // adiciona um novo significado no início da lista
        Frase *nova = new Frase(sig);

        if (head == NULL)
        {
            head = nova;
            return;
        }
        Frase *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = nova;
    }

    void imprimir(string output)
    {
        ofstream outfile;
        outfile.open(output, ios_base::app);

        Frase *p = head;
        int i = 1;

        while (p != NULL)
        {
            outfile << i << ". " << p->sig << endl;
            p = p->next;
            i++;
        }
    }

    int tamanho()
    {
        // calcula o tamanho da lista
        int tamanho = 0;
        Frase *aux = head;
        while (aux != NULL)
        {
            aux = aux->next;
            tamanho++;
        }
        return tamanho;
    }
};

class Verbete
{
public:
    string tipo;
    string palavra;
    ListaFrases sentidos;
    char chave;

    Verbete()
    {
        tipo = " ";
        palavra = " ";
    };
    void SetChave(char c) { chave = c; };
    void Imprime(string output)
    {
        ofstream outfile;
        outfile.open(output, ios_base::app);

        outfile << palavra << " (" << tipo << ")" << endl;
        sentidos.imprimir(output);
    };
};

#endif