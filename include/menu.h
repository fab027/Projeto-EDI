#ifndef MENU_H
#define MENU_H

#include "tipos.h"
#include "fila_espera.h"
#include "fila_compradores.h"
#include "pilha_arquivados.h"

/* Exibe o menu principal e retorna a opção escolhida (1-4) */
int menu_principal(void);

/* Cadastra novo potencial cliente */
void menu_cadastrar(FilaEspera *fila);

/* Fluxo completo de "Realizar Contato" */
void menu_realizar_contato(FilaEspera *fila,
                           FilaCompradores *compradores,
                           PilhaArquivados *arquivados);

/* Sub-menu de Relatórios */
void menu_relatorios(const FilaEspera *fila);

#endif /* MENU_H */
