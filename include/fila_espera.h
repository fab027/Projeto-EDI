#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include "tipos.h"

void fila_espera_inicializar(FilaEspera *f);

void fila_espera_enqueue(FilaEspera *f,
                         const char *nome,
                         const char *telefone,
                         const char *email,
                         Data data_captacao);

NoPotencial *fila_espera_dequeue(FilaEspera *f);

void fila_espera_remover_no(FilaEspera *f, NoPotencial *alvo);

NoPotencial *fila_espera_buscar(FilaEspera *f, const char *nome);

NoPotencial *fila_espera_peek(const FilaEspera *f);

int fila_espera_tamanho(const FilaEspera *f);

void fila_espera_destruir(FilaEspera *f);

#endif 
