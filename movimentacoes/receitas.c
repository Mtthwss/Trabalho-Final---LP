#include "receitas.h"

Receitas *criar_receitas(){
    Receitas *lista = (Receitas *) malloc(sizeof(Receitas));
    lista->tamanho = 0;
    lista->receitas = NULL;
    return lista;
}

void adicionar_receita(Receitas *lista, char *cliente, struct receita receita){
    lista->receitas = (struct receita *) realloc(lista->receitas, (lista->tamanho + 1) * sizeof(struct receita));
    lista->receitas[lista->tamanho] = receita;
    strcpy(lista->receitas[lista->tamanho].cliente, cliente);
    lista->tamanho++;
}

void ler_receitas(Receitas *lista){
    FILE *arquivo = fopen("receitas.txt", "r");
    if (arquivo){
        struct receita r;
        char cliente[100];
        int tamanho; 
        
        fscanf(arquivo, "%d ", &tamanho);
        for (; tamanho > 0; tamanho--){
            fscanf(arquivo, "%[^\n]%*c\n", &r.categoria);
            fscanf(arquivo, "%f\n", &r.valor);
            fscanf(arquivo, "%u %u %d\n", &r.data.dia, &r.data.mes, &r.data.ano);
            fscanf(arquivo, "%[^\n]%*c\n", &cliente);

            adicionar_receita(lista, cliente, r);
        }

        fclose(arquivo);
    }
}

void salvar_receitas(Receitas *lista){
    FILE *arquivo = fopen("receitas.txt", "w");

    if (arquivo){
        fprintf(arquivo, "%d\n", lista->tamanho);
        int i;
        for (i = 0; i < lista->tamanho; i++){
            fprintf(arquivo, "%s\n", lista->receitas[i].categoria);
            fprintf(arquivo, "%f\n", lista->receitas[i].valor);
            fprintf(arquivo, "%u %u %d\n", lista->receitas[i].data.dia, lista->receitas[i].data.mes, lista->receitas[i].data.ano);
            fprintf(arquivo, "%s\n", lista->receitas[i].cliente);
        }

        fclose(arquivo);
    }
}