#include "categorias.h"

Categorias *criar_categorias(){
    Categorias *lista = (Categorias *) malloc(sizeof(Categorias));
    lista->tamanho = 0;
    lista->categorias = NULL;
    return lista;
}

void adicionar_categoria(Categorias *lista, char *cliente, char *titulo){
    lista->categorias = (struct categoria *) realloc(lista->categorias, (lista->tamanho + 1) * sizeof(struct categoria));
    strcpy(lista->categorias[lista->tamanho].categoria, titulo);
    strcpy(lista->categorias[lista->tamanho].cliente, cliente);
    lista->tamanho++;
}

void ler_categorias(Categorias *lista){
    int quant;
    char cliente[100], titulo[100];
    FILE *arquivo = fopen("categorias.txt", "r");
    fscanf(arquivo, "%d", &quant);

    for (; quant > 0; quant--){
        fscanf(arquivo, "\n%[^\n]s", &titulo);
        fscanf(arquivo, "\n%[^\n]s", &cliente);
        adicionar_categoria(lista, cliente, titulo);
    }
}

void salvar_categorias(Categorias *lista){
    FILE *arquivo = fopen("categorias.txt", "w");
    fprintf(arquivo, "%d\n", lista->tamanho);

    int i;
    for (i = 0; i < lista->tamanho; i++){
        fprintf(arquivo, "%s\n", lista->categorias[i].categoria);
        fprintf(arquivo, "%s\n", lista->categorias[i].cliente);
    }

    fclose(arquivo);
}