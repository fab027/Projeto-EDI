#ifndef PILHA_ARQUIVADOS_H
#define PILHA_ARQUIVADOS_H

#include "tipos.h"

void pilha_arquivados_inicializar(PilhaArquivados *p);

void pilha_arquivados_push(PilhaArquivados *p, const NoPotencial *base);

NoArquivado *pilha_arquivados_pop(PilhaArquivados *p);

NoArquivado *pilha_arquivados_topo(const PilhaArquivados *p);

int pilha_arquivados_tamanho(const PilhaArquivados *p);

void pilha_arquivados_destruir(PilhaArquivados *p);

#endif 
