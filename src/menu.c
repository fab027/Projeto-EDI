#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "utils.h"

static void exibir_cliente(const NoPotencial *c)
{
    char buf[20];
    formatar_data(c->data_captacao, buf);
    printf("  +----------------------------------------------+\n");
    printf("  | Nome     : %-33s|\n", c->nome);
    printf("  | Telefone : %-33s|\n", c->telefone);
    printf("  | Email    : %-33s|\n", c->email);
    printf("  | Captacao : %-33s|\n", buf);
    printf("  +----------------------------------------------+\n");
}

static void finalizar_compra(NoPotencial *cliente,
                             FilaEspera *fila,
                             FilaCompradores *compradores)
{
    Data      data_nasc;
    Endereco  end;
    char      cpf[15];

    printf("\n  --- Dados adicionais do comprador ---\n");
    data_nasc = ler_data("  Data de nascimento (dd/mm/aaaa): ");

    ler_string("  Rua     : ", end.rua,    sizeof(end.rua));
    ler_string("  Numero  : ", end.numero, sizeof(end.numero));
    ler_string("  Bairro  : ", end.bairro, sizeof(end.bairro));
    ler_string("  Cidade  : ", end.cidade, sizeof(end.cidade));
    ler_string("  Estado  : ", end.estado, sizeof(end.estado));
    ler_string("  CEP     : ", end.cep,    sizeof(end.cep));
    ler_string("  CPF     : ", cpf,        sizeof(cpf));

    fila_compradores_enqueue(compradores, cliente, data_nasc, &end, cpf);
    fila_espera_remover_no(fila, cliente);
    free(cliente);

    printf("\n  Cliente registrado como COMPRADOR. Pedido enfileirado para logistica.\n");
}

static void finalizar_atendimento(NoPotencial *cliente,
                                  FilaEspera *fila,
                                  FilaCompradores *compradores,
                                  PilhaArquivados *arquivados)
{
    char resp[4];
    printf("\n  O cliente comprou o produto? (s/n): ");
    ler_string("", resp, sizeof(resp));

    if (resp[0] == 's' || resp[0] == 'S') {
        finalizar_compra(cliente, fila, compradores);
        return;
    }

    printf("  Deseja arquivar os dados para contato futuro? (s/n): ");
    ler_string("", resp, sizeof(resp));

    if (resp[0] == 's' || resp[0] == 'S') {
        pilha_arquivados_push(arquivados, cliente);
        fila_espera_remover_no(fila, cliente);
        free(cliente);
        printf("\n  Cliente ARQUIVADO.\n");
    } else {
        fila_espera_remover_no(fila, cliente);
        free(cliente);
        printf("\n  Cliente EXCLUIDO definitivamente.\n");
    }
}

int menu_principal(void)
{
    int opcao = 0;
    char buf[8];

    printf("\n");
    printf(" SISTEMA DE CAPTACAO DE CLIENTES \n");
    printf(" 1. Cadastrar cliente \n");
    printf(" 2. Realizar contato \n");
    printf(" 3. Relatorios \n");
    printf(" 4. Sair \n");
    printf("  Opcao: ");
    ler_string("", buf, sizeof(buf));
    opcao = atoi(buf);
    return opcao;
}

void menu_cadastrar(FilaEspera *fila)
{
    char nome[80], telefone[20], email[80];
    Data data_captacao;

    limpar_tela();
    printf("\n  === CADASTRAR CLIENTE ===\n\n");
    ler_string("  Nome     : ", nome,      sizeof(nome));
    ler_string("  Telefone : ", telefone,  sizeof(telefone));
    ler_string("  Email    : ", email,     sizeof(email));
    data_captacao = ler_data("  Data de captacao (dd/mm/aaaa): ");

    fila_espera_enqueue(fila, nome, telefone, email, data_captacao);
    printf("\n  Cliente cadastrado com sucesso!\n");
    pausar();
}

void menu_realizar_contato(FilaEspera *fila,
                           FilaCompradores *compradores,
                           PilhaArquivados *arquivados)
{
    limpar_tela();
    printf("\n  === REALIZAR CONTATO ===\n");

    if (fila_espera_tamanho(fila) == 0) {
        printf("\n  Nenhum cliente aguardando contato.\n");
        pausar();
        return;
    }

    NoPotencial *atual = fila_espera_peek(fila);
    char buf[8], nome_busca[80];
    int continuar = 1;

    while (continuar) {
        limpar_tela();
        printf("\n  === REALIZAR CONTATO ===\n");
        exibir_cliente(atual);

        printf("\n  1. Proximo cliente\n");
        printf("  2. Cliente anterior\n");
        printf("  3. Buscar por nome\n");
        printf("  4. Finalizar atendimento\n");
        printf("  0. Voltar ao menu principal\n");
        printf("  Opcao: ");
        ler_string("", buf, sizeof(buf));

        switch (atoi(buf)) {
        case 1:
            if (atual->prox != NULL) {
                atual = atual->prox;
            } else {
                printf("\n  Ultimo cliente da lista.\n");
                pausar();
            }
            break;

        case 2: {
            if (atual == fila_espera_peek(fila)) {
                printf("\n  Este e o primeiro cliente da lista.\n");
                pausar();
            } else {
                NoPotencial *ant = fila_espera_peek(fila);
                while (ant->prox != atual) ant = ant->prox;
                atual = ant;
            }
            break;
        }

        case 3:
            ler_string("  Nome (exato): ", nome_busca, sizeof(nome_busca));
            {
                NoPotencial *encontrado = fila_espera_buscar(fila, nome_busca);
                if (encontrado != NULL) {
                    atual = encontrado;
                } else {
                    printf("\n  Cliente nao encontrado. Mantendo cliente atual.\n");
                    pausar();
                }
            }
            break;

        case 4:
            finalizar_atendimento(atual, fila, compradores, arquivados);
            pausar();
            continuar = 0;
            break;

        case 0:
            continuar = 0;
            break;

        default:
            printf("\n  Opcao invalida.\n");
            pausar();
            break;
        }

        if (fila_espera_tamanho(fila) == 0) {
            continuar = 0;
        }
    }
}

void menu_relatorios(const FilaEspera *fila)
{
    char buf[8];
    int continuar = 1;

    while (continuar) {
        limpar_tela();
        printf("\n  === RELATORIOS ===\n\n");
        printf("  1. Numero de clientes aguardando contato\n");
        printf("  2. Lista de clientes com dias de espera\n");
        printf("  0. Voltar\n");
        printf("  Opcao: ");
        ler_string("", buf, sizeof(buf));

        switch (atoi(buf)) {
        case 1:
            printf("\n  Clientes aguardando contato: %d\n",
                   fila_espera_tamanho(fila));
            pausar();
            break;

        case 2: {
            limpar_tela();
            printf("\n  === CLIENTES AGUARDANDO CONTATO ===\n\n");
            if (fila_espera_tamanho(fila) == 0) {
                printf("  Nenhum cliente na fila.\n");
            } else {
                Data hoje = data_hoje();
                const NoPotencial *atual = fila->frente;
                int i = 1;
                while (atual != NULL) {
                    char data_buf[20];
                    formatar_data(atual->data_captacao, data_buf);
                    int dias = diferenca_dias(atual->data_captacao, hoje);
                    printf("  %2d. %-30s | Captado em %s | %d dia(s)\n",
                           i++, atual->nome, data_buf, dias);
                    atual = atual->prox;
                }
            }
            pausar();
            break;
        }

        case 0:
            continuar = 0;
            break;

        default:
            printf("\n  Opcao invalida.\n");
            pausar();
            break;
        }
    }
}
