#ifndef TIPOS_H
#define TIPOS_H

/* ============================================================
 * tipos.h — Definição das estruturas de dados do sistema
 * ============================================================ */

/* Data simples */
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

/* Endereço completo */
typedef struct {
    char rua[100];
    char numero[10];
    char bairro[60];
    char cidade[60];
    char estado[3];   /* UF + '\0' */
    char cep[10];     /* 00000-000 + '\0' */
} Endereco;

/* -------------------------------------------------------
 * Nó da FILA de espera (lista encadeada simples — FIFO)
 * ------------------------------------------------------- */
typedef struct NoPotencial {
    char nome[80];
    char telefone[20];
    char email[80];
    Data  data_captacao;
    struct NoPotencial *prox;
} NoPotencial;

/* -------------------------------------------------------
 * Nó da FILA de compradores (FIFO — pedido chegou, sai na ordem)
 * ------------------------------------------------------- */
typedef struct NoComprador {
    char nome[80];
    char telefone[20];
    char email[80];
    Data  data_captacao;
    /* dados adicionais */
    Data     data_nascimento;
    Endereco endereco;
    char     cpf[15];   /* 000.000.000-00 + '\0' */
    struct NoComprador *prox;
} NoComprador;

/* -------------------------------------------------------
 * Nó da PILHA de arquivados (LIFO — acesso rápido ao mais recente)
 * ------------------------------------------------------- */
typedef struct NoArquivado {
    char nome[80];
    char telefone[20];
    char email[80];
    Data  data_captacao;
    struct NoArquivado *prox;  /* topo da pilha */
} NoArquivado;

/* -------------------------------------------------------
 * Estruturas que encapsulam cada coleção
 * ------------------------------------------------------- */

/* Fila de potenciais clientes (aguardando contato) */
typedef struct {
    NoPotencial *frente;
    NoPotencial *tras;
    int tamanho;
} FilaEspera;

/* Fila de compradores */
typedef struct {
    NoComprador *frente;
    NoComprador *tras;
    int tamanho;
} FilaCompradores;

/* Pilha de arquivados */
typedef struct {
    NoArquivado *topo;
    int tamanho;
} PilhaArquivados;

#endif /* TIPOS_H */
