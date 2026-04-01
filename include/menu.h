#ifndef MENU_H
#define MENU_H

#include "tipos.h"
#include "fila_espera.h"
#include "fila_compradores.h"
#include "pilha_arquivados.h"

int menu_principal(void);

void menu_cadastrar(FilaEspera *fila);

void menu_realizar_contato(FilaEspera *fila,
                           FilaCompradores *compradores,
                           PilhaArquivados *arquivados);

void menu_relatorios(const FilaEspera *fila);

#endif 
