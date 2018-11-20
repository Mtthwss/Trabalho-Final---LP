#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct endereco {
    char logradouro[50];
    char endereco[100];
    unsigned short numero;
    char bairro[50];
    char cidade[100];
    char estado[50];
};

struct telefone {
    unsigned short int ddd;
    char telefone[11];
};

struct data {
    unsigned short dia;
    unsigned short mes;
    unsigned short ano;
};

struct cliente {
    char nome[100];
    char email[250];
    struct endereco endereco;
    struct telefone telefone;
    struct data nascimento;
};

typedef struct {
    int tamanho;
    struct cliente *clientes;
} Clientes;

Clientes *criar_clientes();
void adicionar_cliente(Clientes *, struct cliente);
int remover_clientes(Clientes *, char *);
int buscar_cliente(Clientes *, char *);

void ler_clientes(Clientes *);
void salvar_clientes(Clientes *);

#endif