#include "ListaEncadeada.hpp"

void ListaEncadeada::InsereItem(Verbete verb)
{
    Celula_Verbete *p = new Celula_Verbete();
    Celula_Verbete *q = new Celula_Verbete();

    q = primeiro;
    p = q;

    // inserção em ordem lexicográfica
    for (int i = 1; i <= tamanho; i++)
    {
        q = q->prox;

        if (((q->verbete).palavra < verb.palavra) ||
            (((q->verbete).palavra == verb.palavra) && ((q->verbete).tipo < verb.tipo)))
        {
            p = q;
        }
    }

    Celula_Verbete *nova = new Celula_Verbete();
    nova->verbete = verb;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;

    if (nova->prox == NULL)
        ultimo = nova;
};

void ListaEncadeada::Replace(Verbete verb, string sig)
{
    Celula_Verbete *p;
    p = primeiro->prox;
    int i = 0, pos = 0;

    while (p != NULL)
    {
        i++;
        if ((verb.palavra == p->verbete.palavra) && (verb.tipo == p->verbete.tipo))
        {
            pos = i; // calcula a posição do verbete desatualizado
            break;
        }
        p = p->prox;
    }
    verb.sentidos.adicionar_sig(sig);
    this->SetItem(verb, pos); // substitui o verbete atualizado na posição do desatualizado
}

ListaEncadeada::ListaEncadeada()
{
    primeiro = new Celula_Verbete();
    ultimo = primeiro;
    tamanho = 0;
}

ListaEncadeada::~ListaEncadeada()
{
    Limpa();
    delete primeiro;
}

Celula_Verbete *ListaEncadeada::Posiciona(int pos, bool antes = false)
{
    Celula_Verbete *p;
    int i;
    erroAssert(tamanho > pos || pos >= 0, "Posição Inválida");

    // Posiciona na posição desejada
    p = primeiro;
    for (i = 1; i < pos; i++)
    {
        p = p->prox;
    }
    if (!antes)
        p = p->prox;
    return p;
}

void ListaEncadeada::SetItem(Verbete verb, int pos)
{
    // Coloca um item em determinada posição
    Celula_Verbete *p;
    p = Posiciona(pos);
    p->verbete = verb;
}

Verbete ListaEncadeada::RemoveItem(Verbete verb)
{
    erroAssert(tamanho > 0, "Lista vazia");

    Verbete aux;
    Celula_Verbete *p, *q;

    p = primeiro;
    while ((p->prox != NULL) && ((p->prox->verbete.palavra != verb.palavra) ||
                                 ((p->prox->verbete.palavra == verb.palavra) && (p->prox->verbete.tipo != verb.tipo))))
        p = p->prox;

    // Remove a célula que tem a mesma palavra e tipo do verbete a ser removido
    q = p->prox;
    p->prox = q->prox;
    aux = q->verbete;
    // q->verbete.sentidos.limpa();
    delete q;
    tamanho--;
    if (p->prox == NULL)
        ultimo = p;

    return aux;
};

void ListaEncadeada::VerbetesVazios()
{
    Celula_Verbete *p;
    p = primeiro->prox;

    while (p != NULL)
    {
        // procura pelos verbetes com pelo menos um significado para remover
        if (p->verbete.sentidos.tamanho() > 0)
        {
            RemoveItem(p->verbete);
        }
        p = p->prox;
    }
}

Verbete ListaEncadeada::Pesquisa(Verbete verb)
{
    Verbete aux;
    Celula_Verbete *p;
    p = primeiro->prox;

    while (p != NULL)
    {
        if ((p->verbete.palavra == verb.palavra) && ((p->verbete.tipo == verb.tipo)))
        {
            aux = p->verbete; // Se a palavra da célula for igual a palavra procurada, é o verbete procurado
            break;
        }
        p = p->prox;
    }
    return aux;
};

void ListaEncadeada::Imprime(string output)
{
    // Imprime em ordem lexicográfica
    Celula_Verbete *p;
    p = primeiro->prox;
    while (p != NULL)
    {
        p->verbete.Imprime(output);
        p = p->prox;
    }
};

void ListaEncadeada::Limpa()
{
    Celula_Verbete *p;
    p = primeiro->prox;
    while (p != NULL)
    {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
};
