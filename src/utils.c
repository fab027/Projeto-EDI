#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void ler_string(const char *prompt, char *dest, int tamanho)
{
    printf("%s", prompt);
    if (fgets(dest, tamanho, stdin) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') {
            dest[len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    }
}

Data ler_data(const char *prompt)
{
    Data d = {0, 0, 0};
    char buf[20];
    int ok = 0;

    while (!ok) {
        ler_string(prompt, buf, (int)sizeof(buf));
        if (sscanf(buf, "%d/%d/%d", &d.dia, &d.mes, &d.ano) == 3) {
            if (d.dia >= 1 && d.dia <= 31 &&
                d.mes >= 1 && d.mes <= 12 &&
                d.ano >= 1900 && d.ano <= 2100) {
                ok = 1;
            } else {
                printf("  Data invalida. Use dd/mm/aaaa.\n");
            }
        } else {
            printf("  Formato invalido. Use dd/mm/aaaa.\n");
        }
    }
    return d;
}

static long data_para_dias(Data d)
{
    int m = d.mes;
    int y = d.ano;
    if (m <= 2) { y--; m += 12; }
    long A = y / 100;
    long B = 2 - A + A / 4;
    return (long)(365.25 * (y + 4716)) +
           (long)(30.6001 * (m + 1)) +
           d.dia + B - 1524;
}

int diferenca_dias(Data data_ini, Data data_fim)
{
    return (int)(data_para_dias(data_fim) - data_para_dias(data_ini));
}

Data data_hoje(void)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    Data d;
    d.dia  = tm_info->tm_mday;
    d.mes  = tm_info->tm_mon + 1;
    d.ano  = tm_info->tm_year + 1900;
    return d;
}

void formatar_data(Data d, char *buf)
{
    sprintf(buf, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

void limpar_tela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(void)
{
    printf("\n  Pressione Enter para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
