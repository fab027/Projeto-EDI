#include <stdio.h>
#include "tipos.h"
#include "fila_espera.h"
#include "fila_compradores.h"
#include "pilha_arquivados.h"
#include "menu.h"
#include "utils.h"

int main(void)
{
    FilaEspera      fila_espera;
    FilaCompradores compradores;
    PilhaArquivados arquivados;

    fila_espera_inicializar(&fila_espera);
    fila_compradores_inicializar(&compradores);
    pilha_arquivados_inicializar(&arquivados);

    int opcao;
    do {
        limpar_tela();
        opcao = menu_principal();

        switch (opcao) {
        case 1:
            menu_cadastrar(&fila_espera);
            break;
        case 2:
            menu_realizar_contato(&fila_espera, &compradores, &arquivados);
            break;
        case 3:
            menu_relatorios(&fila_espera);
            break;
        case 4:
            printf("\n  Encerrando o sistema. Ate logo!\n\n");
            break;
        default:
            printf("\n  Opcao invalida. Tente novamente.\n");
            pausar();
            break;
        }
    } while (opcao != 4);

    /* Libera toda memória alocada dinamicamente */
    fila_espera_destruir(&fila_espera);
    fila_compradores_destruir(&compradores);
    pilha_arquivados_destruir(&arquivados);

    return 0;
}
