#include "receitas.h"

Receitas *criar_receitas(){
    Receitas *lista = (Receitas *) malloc(sizeof(Receitas));
    lista->tamanho = 0;
    lista->receitas = NULL;
    return lista;
}

void adicionar_receita(Receitas *lista, char *cliente, struct receita receita){
    lista->receitas = (struct receita *) realloc(lista->receitas, (lista->tamanho + 1) * sizeof(sizeof(struct receita)));
    lista->receitas[lista->tamanho] = receita;
    strcpy(lista->receitas[lista->tamanho].cliente, cliente);
    lista->tamanho++;
}

void salvar_receitas(Receitas *lista){
    FILE *arquivo = fopen("receitas.txt", "w");

    int i;
    for (i = 0; i < lista->tamanho; i++){
        fprintf(arquivo, "%d %s\n", strlen(lista->receitas[i].cliente), lista->receitas[i].cliente);
    }

    fclose(arquivo);
}