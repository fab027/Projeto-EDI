#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_espera.h"

/* ----------------------------------------------------------
 * JUSTIFICATIVA DA ESTRUTURA:
 *   Fila (FIFO) com lista simplesmente encadeada.
 *   O cliente cadastrado há mais tempo deve ser atendido
 *   primeiro — comportamento clássico de fila.
 *   Mantemos ponteiros para frente (dequeue) e para trás
 *   (enqueue) para que ambas as operações sejam O(1).
 * ---------------------------------------------------------- */

void fila_espera_inicializar(FilaEspera *f)
{
    f->frente  = NULL;
    f->tras    = NULL;
    f->tamanho = 0;
}

/* Enqueue: insere no final da fila. */
void fila_espera_enqueue(FilaEspera *f,
                         const char *nome,
                         const char *telefone,
                         const char *email,
                         Data data_captacao)
{
    NoPotencial *novo = (NoPotencial *)malloc(sizeof(NoPotencial));
    if (novo == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        return;
    }
    strncpy(novo->nome,      nome,      sizeof(novo->nome)      - 1);
    strncpy(novo->telefone,  telefone,  sizeof(novo->telefone)  - 1);
    strncpy(novo->email,     email,     sizeof(novo->email)     - 1);
    novo->nome[sizeof(novo->nome)         - 1] = '\0';
    novo->telefone[sizeof(novo->telefone) - 1] = '\0';
    novo->email[sizeof(novo->email)       - 1] = '\0';
    novo->data_captacao = data_captacao;
    novo->prox = NULL;

    if (f->tras == NULL) {
        /* Fila vazia */
        f->frente = novo;
        f->tras   = novo;
    } else {
        f->tras->prox = novo;
        f->tras       = novo;
    }
    f->tamanho++;
}

/* Dequeue: remove do início (mais antigo). */
NoPotencial *fila_espera_dequeue(FilaEspera *f)
{
    if (f->frente == NULL) return NULL;

    NoPotencial *removido = f->frente;
    f->frente = removido->prox;
    if (f->frente == NULL) f->tras = NULL;  /* fila ficou vazia */
    removido->prox = NULL;
    f->tamanho--;
    return removido;
}

/* Remove nó específico (qualquer posição) — necessário para
 * finalizar atendimento quando o usuário navega até um cliente
 * que não é o primeiro da fila. */
void fila_espera_remover_no(FilaEspera *f, NoPotencial *alvo)
{
    if (f->frente == NULL || alvo == NULL) return;

    /* Caso especial: é o primeiro nó */
    if (f->frente == alvo) {
        fila_espera_dequeue(f);
        /* Nota: dequeue já ajusta ponteiros e decrementa tamanho,
         * mas NÃO libera memória — responsabilidade do chamador. */
        return;
    }

    NoPotencial *ant = f->frente;
    while (ant->prox != NULL && ant->prox != alvo) {
        ant = ant->prox;
    }
    if (ant->prox == alvo) {
        ant->prox = alvo->prox;
        if (alvo == f->tras) f->tras = ant;
        alvo->prox = NULL;
        f->tamanho--;
    }
}

/* Busca linear por nome (correspondência exata). */
NoPotencial *fila_espera_buscar(FilaEspera *f, const char *nome)
{
    NoPotencial *atual = f->frente;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

NoPotencial *fila_espera_peek(const FilaEspera *f)
{
    return f->frente;
}

int fila_espera_tamanho(const FilaEspera *f)
{
    return f->tamanho;
}

/* Libera todos os nós da fila. */
void fila_espera_destruir(FilaEspera *f)
{
    NoPotencial *atual = f->frente;
    while (atual != NULL) {
        NoPotencial *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    f->frente  = NULL;
    f->tras    = NULL;
    f->tamanho = 0;
}
