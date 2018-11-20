#ifndef CATEGORIAS_H
#define CATEGORIAS_H

#include <string.h>
#include <stdlib.h>

#include "../clientes/cliente.h"

struct categoria {
    char categoria[100];
    char cliente[100];
};

typedef struct {
    int tamanho;
    struct categoria *categorias;
} Categorias;

Categorias *criar_categorias();
void adicionar_categoria(Categorias *, char *, char *);

void ler_categorias(Categorias *);
void salvar_categorias(Categorias *);

#endif