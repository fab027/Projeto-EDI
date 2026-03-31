#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

/* Leitura segura de strings (evita buffer overflow e lixo no stdin) */
void ler_string(const char *prompt, char *dest, int tamanho);

/* Leitura e validação de Data */
Data ler_data(const char *prompt);

/* Diferença em dias entre duas datas (data_fim - data_ini) */
int diferenca_dias(Data data_ini, Data data_fim);

/* Data atual do sistema */
Data data_hoje(void);

/* Formata data como dd/mm/aaaa */
void formatar_data(Data d, char *buf);

/* Limpa a tela (portável) */
void limpar_tela(void);

/* Pausa até o usuário pressionar Enter */
void pausar(void);

#endif /* UTILS_H */
