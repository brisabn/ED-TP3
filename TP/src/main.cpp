#include "hash.hpp"
#include "avl.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "msgassert.hpp"

string input, output;
bool use_hash, use_arv;

void parse_args(int argc, char const *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        // seleção do algoritmo de ordenação
        if (string(argv[i]) == "-i")
        {
            input = argv[i + 1];
        }
        if (string(argv[i]) == "-o")
        {
            output = argv[i + 1];
        }
        if (string(argv[i]) == "-t")
        {
            if (string(argv[i + 1]) == "hash")
                use_hash = true;
            else if (string(argv[i + 1]) == "arv")
                use_arv = true;
            else
                erroAssert(string(argv[i + 1]) == "hash" || string(argv[i + 1]) == "arv", "Método de dicionário não definido");
        }
    }
}

int main(int argc, char const *argv[])
{
    parse_args(argc, argv);

    ifstream input_file;
    ofstream output_file;

    erroAssert(input[0], "Arquivo de entrada não definido");
    erroAssert(output[0], "Arquivo de saída não definido");

    string line;

    input_file.open(input);
    erroAssert(input_file, "Erro na abertura do arquivo de entrada");

    output_file.open(output);
    erroAssert(output_file, "Erro na abertura do arquivo de saída");

    Hash *dic_h = new Hash;
    avl *raiz = NULL;

    while (getline(input_file, line))
    {
        Verbete *verb = new Verbete;
        string significado, tipo, palavra;

        verb->tipo = line[0];
        erroAssert(verb->tipo == "n" || verb->tipo == "a" || verb->tipo == "v", "Não é um nome, adjetivo ou verbo");
        verb->palavra = line.substr(line.find('[') + 1, line.find(']') - 3);
        verb->chave = verb->palavra[0];

        if (line.length() > verb->palavra.length() + 4)
        {
            significado = line.substr(tipo.length() + 1 + verb->palavra.length() + 4, line.length());
            avisoAssert(significado != " ", "A entrada não está no padrão, há um espaço extra depois da palavra");
            verb->sentidos.adicionar_sig(significado);
        }

        if (use_hash)
        {
            if ((dic_h->Pesquisa(*verb).palavra == verb->palavra) &&
                (dic_h->Pesquisa(*verb).tipo == verb->tipo))
            {
                if (significado.length() > 0)
                    dic_h->Atualiza(dic_h->Pesquisa(*verb), significado);
            }
            else
            {
                dic_h->Insere(*verb);
            }
        }

        if (use_arv)
        {
            if ((raiz->Pesquisa(raiz, *verb).palavra == verb->palavra) &&
                (raiz->Pesquisa(raiz, *verb).tipo == verb->tipo))
            {
                if (significado.length() > 0)
                    raiz->Atualiza(raiz->Pesquisa_raiz(raiz, *verb), raiz->Pesquisa(raiz, *verb), significado);
            }
            else
            {
                raiz = raiz->Insere(raiz, *verb);
            }
        }
    }

    if (use_arv)
    {
        raiz->Display(raiz, output);
        raiz = raiz->Remove_verbs(raiz);
        raiz->Display(raiz, output);
        raiz->Destroi(raiz);
    }
    if (use_hash)
    {
        dic_h->Display(output);
        dic_h->Remove_Verbs();
        dic_h->Display(output);
        dic_h->Destroi();
    }

    return 0;
}
