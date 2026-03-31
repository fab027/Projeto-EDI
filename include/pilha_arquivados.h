#ifndef PILHA_ARQUIVADOS_H
#define PILHA_ARQUIVADOS_H

#include "tipos.h"

void pilha_arquivados_inicializar(PilhaArquivados *p);

/* Empilha cliente arquivado (push) */
void pilha_arquivados_push(PilhaArquivados *p, const NoPotencial *base);

/* Desempilha (pop) — retorna NULL se vazia.
 * Chamador deve liberar a memória. */
NoArquivado *pilha_arquivados_pop(PilhaArquivados *p);

/* Consulta o topo sem remover */
NoArquivado *pilha_arquivados_topo(const PilhaArquivados *p);

int pilha_arquivados_tamanho(const PilhaArquivados *p);

void pilha_arquivados_destruir(PilhaArquivados *p);

#endif /* PILHA_ARQUIVADOS_H */
