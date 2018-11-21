#include "../clientes/cliente.h"

Clientes *criar_clientes(){
    Clientes *lista = (Clientes *) malloc(sizeof(Clientes));
    lista->tamanho = 0;
    lista->clientes = NULL;
    return lista;
}

int buscabinaria(Clientes *vetor, struct cliente c, int inicio, int fim){
    int meio = (inicio + fim) / 2;

    if (meio >= vetor->tamanho)
        return meio;
    if (strcmp(vetor->clientes[meio].nome, c.nome) == 0)
        return meio;
    if (inicio > fim)
        return inicio;
    else if (strcmp(vetor->clientes[meio].nome, c.nome) > 0)
        return buscabinaria(vetor, c, inicio, meio - 1);
    else
        return buscabinaria(vetor, c, meio + 1, fim);
}

int buscar_cliente(Clientes *lista, char *nome){
    struct cliente c;
    strcpy(c.nome, nome);
    int index = buscabinaria(lista, c, 0, lista->tamanho - 1);
    if (index >= 0 && index < lista->tamanho)
        if (strcmp(lista->clientes[index].nome, c.nome) == 0)
            return index;
    return -1;
}

void adicionar_cliente(Clientes *lista, struct cliente cliente){
    lista->clientes = (struct cliente *) realloc(lista->clientes, (lista->tamanho + 1) * sizeof(struct cliente));

    int index = buscabinaria(lista, cliente, 0, lista->tamanho - 1);

    int i;
    for (i = lista->tamanho; i > index; i--)
        lista->clientes[i] = lista->clientes[i - 1];

    lista->clientes[index] = cliente;
    lista->tamanho++;
}

int remover_clientes(Clientes *lista, char *nome){
    struct cliente c;
    strcpy(c.nome, nome);

    int index = buscabinaria(lista, c, 0, lista->tamanho - 1);
    if (strcmp(lista->clientes[index].nome, c.nome) == 0){
        for (; index < lista->tamanho - 1; index++){
            lista->clientes[index] = lista->clientes[index + 1];
        }
        lista->clientes = (struct cliente *) realloc(lista->clientes, (lista->tamanho - 1) * sizeof(struct cliente));
        lista->tamanho--;
        return 0;
    }
    return -1;
}

void ler_clientes(Clientes *lista){
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo){
        struct cliente c;
        int tamanho;

        fscanf(arquivo, "%d ", &tamanho);

        for (; tamanho > 0; tamanho--){
            fscanf(arquivo, "%[^\n]%*c\n", &c.nome);
            fscanf(arquivo, "%[^\n]%*c\n", &c.email);
            fscanf(arquivo, "%[^\n]%*c\n", &c.endereco.logradouro);
            fscanf(arquivo, "%[^\n]%*c\n", &c.endereco.endereco);
            fscanf(arquivo, "%d\n", &c.endereco.numero);
            fscanf(arquivo, "%[^\n]%*c\n", &c.endereco.bairro);
            fscanf(arquivo, "%[^\n]%*c\n", &c.endereco.cidade);
            fscanf(arquivo, "%[^\n]%*c\n", &c.endereco.estado);
            fscanf(arquivo, "%d\n", &c.telefone.ddd);
            fscanf(arquivo, "%[^\n]%*c\n", &c.telefone.telefone);
            fscanf(arquivo, "%d\n", &c.nascimento.ano);
            fscanf(arquivo, "%u\n", &c.nascimento.dia);
            fscanf(arquivo, "%u\n", &c.nascimento.mes);
            adicionar_cliente(lista, c);
        }

        fclose(arquivo);
    }
}

void salvar_clientes(Clientes *lista){
    FILE *arquivo;
    arquivo = fopen("clientes.txt", "w");

    if (arquivo){
        fprintf(arquivo, "%d\n", lista->tamanho);
        int i;
        for (i = 0; i < lista->tamanho; i++){
            fprintf(arquivo, "%s\n", lista->clientes[i].nome);
            fprintf(arquivo, "%s\n", lista->clientes[i].email);
            fprintf(arquivo, "%s\n", lista->clientes[i].endereco.logradouro);
            fprintf(arquivo, "%s\n", lista->clientes[i].endereco.endereco);
            fprintf(arquivo, "%d\n", lista->clientes[i].endereco.numero);
            fprintf(arquivo, "%s\n", lista->clientes[i].endereco.bairro);
            fprintf(arquivo, "%s\n", lista->clientes[i].endereco.cidade);
            fprintf(arquivo, "%s\n", lista->clientes[i].endereco.estado);
            fprintf(arquivo, "%d\n", lista->clientes[i].telefone.ddd);
            fprintf(arquivo, "%s\n", lista->clientes[i].telefone.telefone);
            fprintf(arquivo, "%d\n", lista->clientes[i].nascimento.ano);
            fprintf(arquivo, "%u\n", lista->clientes[i].nascimento.dia);
            fprintf(arquivo, "%u\n", lista->clientes[i].nascimento.mes);
        }

        fclose(arquivo);
    } else {
        fprintf(stderr, "Erro ao salvar - salvar_clientes();.\n");
        exit(1);
    }
}