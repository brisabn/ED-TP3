#include "avl.hpp"

// Muda o verbete da raiz do parâmetro para um verbete atualizado
void avl::Atualiza(avl *raiz, Verbete verb, string atualiza)
{
    verb.sentidos.adicionar_sig(atualiza);
    raiz->verbete = verb;
}

// Pesquisa a raiz de acordo com o verbete fornecido
avl *avl::Pesquisa_raiz(avl *raiz, Verbete verb)
{
    avl *aux = NULL;
    if (raiz == NULL)
    {
        return aux;
    }
    else if ((verb.palavra > raiz->verbete.palavra) ||
             ((verb.palavra == raiz->verbete.palavra) && (verb.tipo > raiz->verbete.tipo)))
    {
        aux = Pesquisa_raiz(raiz->dir, verb);
        return aux;
    }
    else if ((verb.palavra < raiz->verbete.palavra) ||
             ((verb.palavra == raiz->verbete.palavra) && (verb.tipo < raiz->verbete.tipo)))
    {
        aux = Pesquisa_raiz(raiz->esq, verb);
        return aux;
    }
    else
    {
        aux = raiz;
        return aux;
    }
    return aux;
}

// Pesquisa na raiz o verbete fornecido
Verbete avl::Pesquisa(avl *raiz, Verbete verb)
{
    Verbete aux;
    if (raiz == NULL)
    {
        return aux;
    }
    else if ((verb.palavra > raiz->verbete.palavra) ||
             ((verb.palavra == raiz->verbete.palavra) && (verb.tipo > raiz->verbete.tipo)))
    {
        aux = Pesquisa(raiz->dir, verb);
        return aux;
    }
    else if ((verb.palavra < raiz->verbete.palavra) ||
             ((verb.palavra == raiz->verbete.palavra) && (verb.tipo < raiz->verbete.tipo)))
    {
        aux = Pesquisa(raiz->esq, verb);
        return aux;
    }
    else
    {
        aux = raiz->verbete;
        return aux;
    }

    return aux;
}

// Retorna a altura da raiz
int avl::getAltura(avl *raiz)
{
    if (raiz == NULL)
        return 0;
    return raiz->altura;
}

int max(int a, int b) { return (a > b) ? a : b; }

// Rotaciona para direita
avl *avl::dirRotate(avl *raiz_y)
{
    avl *raiz_x = raiz_y->esq;
    avl *raiz = raiz_x->dir;

    raiz_x->dir = raiz_y;
    raiz_y->esq = raiz;

    raiz_y->altura = max(getAltura(raiz_y->esq), getAltura(raiz_y->dir)) + 1;
    raiz_x->altura = max(getAltura(raiz_x->esq), getAltura(raiz_x->dir)) + 1;

    // a raiz_x é a balanceada
    return raiz_x;
}

avl *avl::esqRotate(avl *raiz_x)
{
    avl *raiz_y = raiz_x->dir;
    avl *raiz = raiz_y->esq;

    raiz_y->esq = raiz_x;
    raiz_x->dir = raiz;

    raiz_x->altura = max(getAltura(raiz_x->esq), getAltura(raiz_x->dir)) + 1;
    raiz_y->altura = max(getAltura(raiz_y->esq), getAltura(raiz_y->dir)) + 1;

    // a raiz_y é a balanceada
    return raiz_y;
}

// Calcula o balanceamento, ou seja, verifica se as alturas dos dois lados são compatíveis
int avl::getBalance(avl *raiz)
{
    if (raiz == NULL)
        return 0;
    return getAltura(raiz->esq) - getAltura(raiz->dir);
}

avl *avl::Insere(avl *raiz, Verbete verb)
{
    // Inserção normal de árvore binária de pesquisa
    if (raiz == NULL)
    {
        avl *raiz = new avl(verb);
        return raiz;
    }

    if ((verb.palavra > raiz->verbete.palavra) ||
        ((verb.palavra == raiz->verbete.palavra) && (verb.tipo > raiz->verbete.tipo)))
        raiz->dir = Insere(raiz->dir, verb);
    else if ((verb.palavra < raiz->verbete.palavra) ||
             ((verb.palavra == raiz->verbete.palavra) && (verb.tipo < raiz->verbete.tipo)))
        raiz->esq = Insere(raiz->esq, verb);
    else
    {
        return raiz;
    }

    // Balanceamento da árvore
    raiz->altura = 1 + max(getAltura(raiz->esq), getAltura(raiz->dir));
    int balance = getBalance(raiz);

    // Caso em que o lado direito está desbalanceado
    if (balance > 1 && verb.palavra < raiz->esq->verbete.palavra)
        return dirRotate(raiz);

    // Caso em que o lado esquedo está desbalanceado
    if (balance < -1 && verb.palavra > raiz->dir->verbete.palavra)
        return esqRotate(raiz);

    // Caso em que o lado da esquerda está balanceado com um nó desbalanceado na direita
    if (balance > 1 && verb.palavra > raiz->esq->verbete.palavra)
    {
        raiz->esq = esqRotate(raiz->esq);
        return dirRotate(raiz);
    }
    // Caso em que o lado da direita está balanceado com um nó desbalanceado na esquerda
    if (balance < -1 && verb.palavra < raiz->dir->verbete.palavra)
    {
        raiz->dir = dirRotate(raiz->dir);
        return esqRotate(raiz);
    }
    return raiz;
}

// Retorna o nó mínimo da árvore
avl *avl::noduloMinimo(avl *raiz)
{
    avl *aux = raiz;

    // o mínimo estará na extrema esquerda da árvore
    while (aux->esq != NULL)
        aux = aux->esq;

    return aux;
}

avl *avl::Remove(avl *raiz, Verbete verb)
{
    // Remoção normal de árvore binária de pesquisa
    if (raiz == NULL)
        return raiz;

    if ((verb.palavra > raiz->verbete.palavra) ||
        ((verb.palavra == raiz->verbete.palavra) && (verb.tipo > raiz->verbete.tipo)))
    {
        raiz->dir = Remove(raiz->dir, verb);
    }
    else if ((verb.palavra < raiz->verbete.palavra) ||
             ((verb.palavra == raiz->verbete.palavra) && (verb.tipo < raiz->verbete.tipo)))
    {
        raiz->esq = Remove(raiz->esq, verb);
    }
    else // A chave é igual e é do mesmo tipo, logo, será deletada
    {
        // raiz tem um ou nenhum filho
        if ((raiz->esq == NULL) || (raiz->dir == NULL))
        {
            avl *aux = raiz->esq ? raiz->esq : raiz->dir;

            if (aux == NULL) // não possui filhos
            {
                aux = raiz;
                raiz = NULL;
            }
            else // posui um filho
                *raiz = *aux;
            aux = nullptr;
        }
        else // possui dois filhos
        {
            avl *aux = noduloMinimo(raiz->dir);
            raiz->verbete = aux->verbete;
            raiz->dir = Remove(raiz->dir, aux->verbete);
        }
    }

    if (raiz == NULL)
        return raiz;

    // Balanceamento da árvore
    raiz->altura = 1 + max(getAltura(raiz->esq), getAltura(raiz->dir));
    int balance = getBalance(raiz);

    // Caso em que o lado direito está desbalanceado
    if (balance > 1 && getBalance(raiz->esq) >= 0)
        return dirRotate(raiz);

    // Caso em que o lado esquedo está desbalanceado
    if (balance < -1 && getBalance(raiz->dir) <= 0)
        return esqRotate(raiz);

    // Caso em que o lado da esquerda está balanceado com um nó desbalanceado na direita
    if (balance > 1 && getBalance(raiz->esq) < 0)
    {
        raiz->esq = esqRotate(raiz->esq);
        return dirRotate(raiz);
    }

    // Caso em que o lado da direita está balanceado com um nó desbalanceado na esquerda
    if (balance < -1 && getBalance(raiz->dir) > 0)
    {
        raiz->dir = dirRotate(raiz->dir);
        return esqRotate(raiz);
    }
    return raiz;
}

// Imprime a árvore em ordem
void avl::Display(avl *raiz, string output)
{
    if (raiz == NULL)
        return;
    Display(raiz->esq, output);
    raiz->verbete.Imprime(output);
    Display(raiz->dir, output);
}

avl *avl::Remove_verbs(avl *&raiz)
{
    if (!raiz)
        return nullptr;

    raiz->esq = Remove_verbs(raiz->esq);
    raiz->dir = Remove_verbs(raiz->dir);

    // Percorre a árvore verfificando se tem pelo menos um significado,
    // Se sim, remove-o
    if (raiz->verbete.sentidos.tamanho() > 0)
    {
        avl *aux;
        aux = Remove(raiz, raiz->verbete);
        raiz = aux;
    }

    return raiz;
}

void avl::Destroi(avl *&raiz)
{
    if (raiz != NULL)
    {
        Destroi(raiz->esq);
        Destroi(raiz->dir);

        // Remove todos os nódulos
        avl *aux;
        aux = Remove(raiz, raiz->verbete);
        raiz = aux;
        // delete raiz;
    }
    raiz = NULL;
}