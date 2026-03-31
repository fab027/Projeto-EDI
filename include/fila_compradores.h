#ifndef FILA_COMPRADORES_H
#define FILA_COMPRADORES_H

#include "tipos.h"

void fila_compradores_inicializar(FilaCompradores *f);

/* Enfileira cliente que comprou (enqueue) */
void fila_compradores_enqueue(FilaCompradores *f,
                              const NoPotencial *base,
                              Data data_nasc,
                              const Endereco *end,
                              const char *cpf);

/* Remove o primeiro da fila (logística processa em ordem de chegada) */
NoComprador *fila_compradores_dequeue(FilaCompradores *f);

int fila_compradores_tamanho(const FilaCompradores *f);

void fila_compradores_destruir(FilaCompradores *f);

#endif /* FILA_COMPRADORES_H */
