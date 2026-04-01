#ifndef TIPOS_H
#define TIPOS_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char rua[100];
    char numero[10];
    char bairro[60];
    char cidade[60];
    char estado[3];   
    char cep[10];     
} Endereco;

typedef struct NoPotencial {
    char nome[80];
    char telefone[20];
    char email[80];
    Data  data_captacao;
    struct NoPotencial *prox;
} NoPotencial;

typedef struct NoComprador {
    char nome[80];
    char telefone[20];
    char email[80];
    Data  data_captacao;
    Data     data_nascimento;
    Endereco endereco;
    char     cpf[15];   
    struct NoComprador *prox;
} NoComprador;

typedef struct NoArquivado {
    char nome[80];
    char telefone[20];
    char email[80];
    Data  data_captacao;
    struct NoArquivado *prox;  
} NoArquivado;

typedef struct {
    NoPotencial *frente;
    NoPotencial *tras;
    int tamanho;
} FilaEspera;

typedef struct {
    NoComprador *frente;
    NoComprador *tras;
    int tamanho;
} FilaCompradores;

typedef struct {
    NoArquivado *topo;
    int tamanho;
} PilhaArquivados;

#endif 
