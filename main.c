#include <stdio.h>
#include <string.h>
#include "clientes/cliente.h"
#include "movimentacoes/receitas.h"
#include "movimentacoes/categorias.h"

Clientes *lista_clientes;
Receitas *lista_receitas;
Categorias *lista_categorias;

int usuario_id;

void carregarlistas();
void finalizar();
void menuprincipal();
void menucliente();
void menunovamovimentacao();
void menuvermovimentacao();

void novousuario();
void usuarioexistente();

void novacategoria();
void listarcategorias();

void novareceita();
void verreceitas();

int main(){
    carregarlistas();
    menuprincipal();
    finalizar();
}

void carregarlistas(){
    lista_clientes = criar_clientes();
    ler_clientes(lista_clientes);
    lista_receitas = criar_receitas();
    lista_categorias = criar_categorias();
    ler_categorias(lista_categorias);
}

void finalizar(){
    salvar_receitas(lista_receitas);
    salvar_clientes(lista_clientes);
    salvar_categorias(lista_categorias);
    exit(1);
}

void menuprincipal(){
    int opcao;

    printf("\E[2J\E[2H");
    printf("-------- MENU --------\n");
    printf("[1] Novo usuario.\n");
    printf("[2] Entrar no sistema.\n");
    printf("\n[0] Sair.\n");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            novousuario();
            break;
        case 2:
            usuarioexistente();
            break;
        case 0:
            return;
            break;
        default:
            menuprincipal();
    }
}

void menucliente(){
    int opcao;
    
    printf("\E[2J\E[2H");
    printf("-------- %s --------\n", lista_clientes->clientes[usuario_id].nome);
    printf("[1] - Nova movimentacao.\n");
    printf("[2] - Remover movimentacao.\n");
    printf("[3] - Ver movimentacoes.\n");
    printf("[4] - Nova categoria de movimentacao.\n");
    printf("[5] - Remover categoria de movimentacao.\n");
    printf("[6] - Ver categorias de movimentacao.\n");
    printf("[9] - Sair do usuario.\n");
    printf("[0] - Finalizar programa.\n");
    
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            menunovamovimentacao();
            break;
        case 2:
            break;
        case 3:
            menuvermovimentacao();
            break;
        case 4:
            novacategoria();
            break;
        case 6:
            listarcategorias();
            break;
        case 9:
            menuprincipal();
            break;
        case 0:
            finalizar();
            break;
        default:
            menucliente();
    }
}

void menunovamovimentacao(){
    int opcao;
    
    printf("\E[2J\E[2H");
    printf("-------- NOVA MOVIMENTACAO --------\n", lista_clientes->clientes[usuario_id].nome);
    printf("[1] - Receitas.\n");
    printf("[2] - Gastos.\n");
    printf("[3] - Investimentos.\n");
    printf("[0] - Retornar.\n");
    
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            novareceita();
            break;
        case 2:
            break;
        case 9:
            menuprincipal();
            break;
        case 0:
            menucliente();
            break;
        default:
            menunovamovimentacao();
    }
}

void menuvermovimentacao(){
    int opcao;
    
    printf("\E[2J\E[2H");
    printf("-------- VER MOVIMENTACOES --------\n", lista_clientes->clientes[usuario_id].nome);
    printf("[1] - Receitas.\n");
    printf("[2] - Gastos.\n");
    printf("[3] - Investimentos.\n");
    printf("[0] - Retornar.\n");
    
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            verreceitas();
            break;
        case 2:
            break;
        case 9:
            break;
        case 0:
            menucliente();
            break;
        default:
            menunovamovimentacao();
    }
}

void novousuario(){
    struct cliente cliente;

    printf("\E[2J\E[2H");
    printf("-------- BEM VINDO --------\n");
    printf("Para continuar, preencha as informacoes a seguir: \n");
    printf("Insira seu nome: ");
    scanf("\n%[^\n]s", &cliente.nome);
    printf("Insira seu email: ");
    scanf("\n%[^\n]s", &cliente.email);
    printf("Insira seu logradouro (Ex. Rua, Avenida): ");
    scanf("\n%[^\n]s", &cliente.endereco.logradouro);
    printf("Insira o nome do seu logradouro: ");
    scanf("\n%[^\n]s", &cliente.endereco.endereco);
    printf("Insira o numero da sua residencia: ");
    scanf("%d", &cliente.endereco.numero);
    printf("Insira o nome do seu bairro: ");
    scanf("\n%[^\n]s", &cliente.endereco.bairro);
    printf("Insira o nome da sua cidade: ");
    scanf("\n%[^\n]s", &cliente.endereco.cidade);
    printf("Insira o nome do seu estado: ");
    scanf("\n%[^\n]s", &cliente.endereco.estado);
    printf("\nQual o dia do seu nascimento? (Ex. 15) ");
    scanf("%d", &cliente.nascimento.dia);
    printf("Qual o mes do seu nascimento? (Ex. 08) ");
    scanf("%d", &cliente.nascimento.mes);
    printf("Qual o ano do seu nascimento? (Ex. 2000) ");
    scanf("%d", &cliente.nascimento.ano);
    printf("\nQual o DDD do seu telefone? (Ex. 93, 98) ");
    scanf("%d", &cliente.telefone.ddd);
    printf("Qual o numero do seu telefone? (Ex. 991000000) ");
    scanf("%s", &cliente.telefone.telefone);

    adicionar_cliente(lista_clientes, cliente);
    printf("\nCadastro concluido com sucesso.\n");
    printf("Deseja voltar ao menu? Caso contrario, o programa sera finalizado. (Y/N): ");

    char escolha;
    scanf("\n%c", &escolha);

    if (escolha == 'Y')
        menuprincipal();
    else
        finalizar();
}

void usuarioexistente(){
    char nome[100], escolha;
    int encontrado = 0;

    printf("\E[2J\E[2H");
    printf("-------- BEM VINDO --------\n");
    printf("Insira o seu nome: ");
    scanf("\n%[^\n]s", &nome);

    encontrado = buscar_cliente(lista_clientes, nome);

    if (encontrado != -1){
        if (strcmp(lista_clientes->clientes[encontrado].nome, nome) == 0){
            usuario_id = encontrado;
            menucliente();
        }
    } else {
        printf("\nNao ha nenhum usuario cadastrado com este nome.\nDeseja tentar novamente?\nCaso contrario, voltaremos ao menu principal. (Y/N): ");
        scanf("\n%c", &escolha);
        if (escolha == 'Y')
            usuarioexistente();
        else
            menuprincipal();
    }
}

void novacategoria(){
    char titulo[100], escolha;
    
    printf("\E[2J\E[2H");
    printf("-------- NOVA CATEGORIA --------\n");
    printf("Insira o titulo da sua nova categoria: ");
    scanf("\n%[^\n]s", &titulo);

    adicionar_categoria(lista_categorias, lista_clientes->clientes[usuario_id].email, titulo);
    printf("Categoria adicionada com sucesso.\nDeseja retornar? Caso contrario, finalizaremos o programa. (Y/N) ");

    scanf("\n%c", &escolha);
    if (escolha == 'Y')
        menucliente();
    else
        finalizar();
}

void listarcategorias(){
    int i, count;
    char escolha;

    printf("\E[2J\E[2H");
    printf("-------- CATEGORIAS --------\n");

    for (i = 0, count = 0; i < lista_categorias->tamanho; i++)
        if (strcmp(lista_categorias->categorias[i].cliente, lista_clientes->clientes[usuario_id].email) == 0)
            printf("Categoria %d: %s\n", ++count, lista_categorias->categorias[i].categoria);
    
    printf("\nVoce tem no total, %d categorias cadastradas.\n", count);
    printf("\nDeseja retornar? Caso contrario, finalizaremos o programa. (Y/N) ");

    scanf("\n%c", &escolha);
    if (escolha == 'Y')
        menucliente();
    else
        finalizar();    
}

void novareceita(){
    char escolha;
    int i;
    struct receita novareceita;

    printf("\E[2J\E[2H");
    printf("-------- NOVA RECEITA --------\n");

    if (lista_categorias->tamanho == 0){
        printf("Voce nao tem categorias cadastradas. Por favor, cadastre primeiro.\n");
    } else {
        for (i = 0; i < lista_categorias->tamanho; i++)
            if (strcmp(lista_categorias->categorias[i].cliente, lista_clientes->clientes[usuario_id].email) == 0)
                printf("[%d] - %s\n", i, lista_categorias->categorias[i].categoria);
        printf("Por favor, insira o numero correspondente da categoria desejada: ");
        scanf("\n%d", &i);
        if (i < 0 || i >= lista_categorias->tamanho){
            printf("Voce escolheu uma categoria invalida.\n");
        } else {
            printf("Insira o valor: ");
            scanf("%f", &novareceita.valor);
            printf("\nInsira o dia: ");
            scanf("%d", &novareceita.data.dia);
            printf("Insira o mes: ");
            scanf("%d", &novareceita.data.mes);
            printf("Insira o ano: ");
            scanf("%d", &novareceita.data.ano);

            strcpy(novareceita.categoria, lista_categorias->categorias[i].categoria);
            adicionar_receita(lista_receitas, lista_clientes->clientes[usuario_id].email, novareceita);

            printf("\nReceita adicionada com sucesso!\n");
        }
    }

    printf("\nDeseja retornar? Caso contrario, finalizaremos o programa. (Y/N) ");

    scanf("\n%c", &escolha);
    if (escolha == 'Y')
        menunovamovimentacao();
    else
        finalizar();
}

void verreceitas(){
    int i, count;
    char escolha;

    printf("\E[2J\E[2H");
    printf("-------- VER RECEITAS --------\n");

    printf("Voce registrou %d receitas.\n", lista_receitas->tamanho);

    for (i = 0, count = 0; i < lista_receitas->tamanho; i++){
        if (strcmp(lista_receitas->receitas[i].cliente, lista_clientes->clientes[usuario_id].email) == 0){
            printf("Receita %d:\n", ++count);
            printf("Categoria: %s\n", lista_receitas->receitas[i].categoria);
            printf("Data: %d/%d/%d\n", lista_receitas->receitas[i].data.dia, lista_receitas->receitas[i].data.mes, lista_receitas->receitas[i].data.ano);
            printf("Valor: %.2f\n", lista_receitas->receitas[i].valor);
        }
    }

    printf("\nDeseja retornar? Caso contrario, finalizaremos o programa. (Y/N) ");

    scanf("\n%c", &escolha);
    if (escolha == 'Y')
        menunovamovimentacao();
    else
        finalizar();
}