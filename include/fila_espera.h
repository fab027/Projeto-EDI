#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include "tipos.h"

/* Inicializa a fila (deve ser chamado antes de qualquer outra operação) */
void fila_espera_inicializar(FilaEspera *f);

/* Enfileira um novo potencial cliente (enqueue) */
void fila_espera_enqueue(FilaEspera *f,
                         const char *nome,
                         const char *telefone,
                         const char *email,
                         Data data_captacao);

/* Remove e retorna o cliente mais antigo (dequeue).
 * Retorna NULL se a fila estiver vazia.
 * O CHAMADOR é responsável por liberar a memória do nó retornado. */
NoPotencial *fila_espera_dequeue(FilaEspera *f);

/* Remove um nó específico (identificado por ponteiro) sem dequeue normal.
 * Usado quando o usuário escolhe o cliente a atender pelo nome. */
void fila_espera_remover_no(FilaEspera *f, NoPotencial *alvo);

/* Busca por nome (correspondência exata, retorna NULL se não encontrado) */
NoPotencial *fila_espera_buscar(FilaEspera *f, const char *nome);

/* Consulta o próximo sem remover */
NoPotencial *fila_espera_peek(const FilaEspera *f);

/* Número de clientes na fila */
int fila_espera_tamanho(const FilaEspera *f);

/* Libera toda a memória alocada */
void fila_espera_destruir(FilaEspera *f);

#endif /* FILA_ESPERA_H */
