#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_compradores.h"

void fila_compradores_inicializar(FilaCompradores *f)
{
    f->frente  = NULL;
    f->tras    = NULL;
    f->tamanho = 0;
}

void fila_compradores_enqueue(FilaCompradores *f,
                              const NoPotencial *base,
                              Data data_nasc,
                              const Endereco *end,
                              const char *cpf)
{
    NoComprador *novo = (NoComprador *)malloc(sizeof(NoComprador));
    if (novo == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        return;
    }
    
    strncpy(novo->nome,     base->nome,     sizeof(novo->nome)     - 1);
    strncpy(novo->telefone, base->telefone, sizeof(novo->telefone) - 1);
    strncpy(novo->email,    base->email,    sizeof(novo->email)    - 1);
    novo->nome[sizeof(novo->nome)         - 1] = '\0';
    novo->telefone[sizeof(novo->telefone) - 1] = '\0';
    novo->email[sizeof(novo->email)       - 1] = '\0';
    novo->data_captacao = base->data_captacao;

    novo->data_nascimento = data_nasc;
    novo->endereco = *end;
    strncpy(novo->cpf, cpf, sizeof(novo->cpf) - 1);
    novo->cpf[sizeof(novo->cpf) - 1] = '\0';
    novo->prox = NULL;

    if (f->tras == NULL) {
        f->frente = novo;
        f->tras   = novo;
    } else {
        f->tras->prox = novo;
        f->tras       = novo;
    }
    f->tamanho++;
}

NoComprador *fila_compradores_dequeue(FilaCompradores *f)
{
    if (f->frente == NULL) return NULL;
    NoComprador *removido = f->frente;
    f->frente = removido->prox;
    if (f->frente == NULL) f->tras = NULL;
    removido->prox = NULL;
    f->tamanho--;
    return removido;
}

int fila_compradores_tamanho(const FilaCompradores *f)
{
    return f->tamanho;
}

void fila_compradores_destruir(FilaCompradores *f)
{
    NoComprador *atual = f->frente;
    while (atual != NULL) {
        NoComprador *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    f->frente  = NULL;
    f->tras    = NULL;
    f->tamanho = 0;
}
