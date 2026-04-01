#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

void ler_string(const char *prompt, char *dest, int tamanho);

Data ler_data(const char *prompt);

int diferenca_dias(Data data_ini, Data data_fim);

Data data_hoje(void);

void formatar_data(Data d, char *buf);

void limpar_tela(void);

void pausar(void);

#endif 
