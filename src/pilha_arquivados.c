#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha_arquivados.h"

void pilha_arquivados_inicializar(PilhaArquivados *p)
{
    p->topo    = NULL;
    p->tamanho = 0;
}

void pilha_arquivados_push(PilhaArquivados *p, const NoPotencial *base)
{
    NoArquivado *novo = (NoArquivado *)malloc(sizeof(NoArquivado));
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

    novo->prox = p->topo;
    p->topo    = novo;
    p->tamanho++;
}

NoArquivado *pilha_arquivados_pop(PilhaArquivados *p)
{
    if (p->topo == NULL) return NULL;
    NoArquivado *removido = p->topo;
    p->topo    = removido->prox;
    removido->prox = NULL;
    p->tamanho--;
    return removido;
}

NoArquivado *pilha_arquivados_topo(const PilhaArquivados *p)
{
    return p->topo;
}

int pilha_arquivados_tamanho(const PilhaArquivados *p)
{
    return p->tamanho;
}

void pilha_arquivados_destruir(PilhaArquivados *p)
{
    NoArquivado *atual = p->topo;
    while (atual != NULL) {
        NoArquivado *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    p->topo    = NULL;
    p->tamanho = 0;
}
