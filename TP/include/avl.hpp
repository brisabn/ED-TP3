#ifndef AVL_HPP
#define AVL_HPP

#include "significados.hpp"

class avl
{
public:
    Verbete verbete;
    avl *esq;
    avl *dir;
    int altura;

    avl(Verbete verb)
    {
        this->verbete = verb;
        this->esq = NULL;
        this->dir = NULL;
        this->altura = 1;
    }

    // Funções Dicionário
    Verbete Pesquisa(avl *, Verbete);
    avl *Insere(avl *, Verbete);
    void Atualiza(avl *, Verbete, string);
    avl *Remove(avl *, Verbete);
    void Destroi(avl *&);

    void Display(avl *, string);
    avl *Remove_verbs(avl *&);

    // Funções auxiliares
    int getAltura(avl *);
    avl *Pesquisa_raiz(avl *, Verbete);
    avl *noduloMinimo(avl *);
    avl *dirRotate(avl *);
    avl *esqRotate(avl *);
    int getBalance(avl *);
};

#endif