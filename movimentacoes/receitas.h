#ifndef RECEITAS_H
#define RECEITAS_H

#include <stdlib.h>
#include "../clientes/cliente.h"

struct receita {
    char categoria[50];
    float valor;
    struct data data;
    char cliente[100];
};

typedef struct {
    int tamanho;
    struct receita *receitas;
} Receitas;

Receitas *criar_receitas();
void adicionar_receita(Receitas *, char *, struct receita);

void salvar_receitas(Receitas *);

#endif