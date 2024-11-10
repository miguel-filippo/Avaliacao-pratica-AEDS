#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "LNSE.h"

/*
    O código abaixo é uma CLI para testar as funcionalidades da LNSE (Lista Não Sequencial Estática)
    implementada no arquivo de header LNSE.h - Miguel Filippo Rocha Calhabeu | ICMC | BSI
*/

void exibirLNSE(LNSE *lnse);

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int exit = 0;
    LNSE *lnse = NULL;

    while (!exit) {
        int option;
        printf("\n=============================================");
        exibirLNSE(lnse);
        printf("\nEscolha uma opção:\n");
        printf("1 - Criar LNSE\n");
        printf("2 - Inserir na LNSE\n");
        printf("3 - Remover da LNSE\n");
        printf("4 - Imprimir LNSE\n");
        printf("5 - Imprimir vetor real\n");
        printf("6 - Limpar a tela\n");
        printf("7 - Sair\n");
        printf("=============================================\n");
        printf("Opção: ");
        scanf("%d", &option);
        printf("\n\n");

        switch (option) {
            case 1: {
                if (lnse != NULL) {
                    printf("LNSE já foi criada!\n");
                    break;
                }

                int capacity;
                printf("Digite a capacidade da LNSE: ");
                scanf("%d", &capacity);

                if (capacity <= 0) {
                    printf("Capacidade inválida!\n");
                    break;
                } else if (capacity > 100) {
                    printf("Capacidade muito grande, fixando capacidade em 100.\n");
                    capacity = 100;
                }

                lnse = criarLNSE(capacity);
                printf("LNSE criada com sucesso!\n");
                break;
            }
            case 2: {
                if (lnse == NULL) {
                    printf("LNSE não foi criada ainda!\n");
                    break;
                }

                int x, i;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &x);
                printf("Digite a posição a ser inserida: ");
                scanf("%d", &i);

                printf("%s\n",inserirLNSE(lnse, x, i));

                break;
            }
            case 3: {
                if (lnse == NULL) {
                    printf("LNSE não foi criada ainda!\n");
                    break;
                }

                int i;
                printf("Digite a posição a ser removida: ");
                scanf("%d", &i);

                int value = removerLNSE(lnse, i);
                printf("Valor removido: %d\n", value);
                break;
            }
            case 4: {
                if (lnse == NULL) {
                    printf("LNSE não foi criada ainda!\n");
                    break;
                }

                printf("%d", sizeLNSE(lnse));
                break;
            }
            case 5: {
                if (lnse == NULL) {
                    printf("LNSE não foi criada ainda!\n");
                    break;
                }

                printf("[ ");
                for (int i = 0; i < lnse->freePositions->capacity; i++) {
                    if (lnse->registers[i].value != -1)printf("%d ", lnse->registers[i].value);
                    else printf(" ");
                    if (i != (lnse->freePositions->capacity - 1))printf("I ");
                }
                printf("]\n");
                break;
            }
            case 6: {
                system("cls");
                break;
            }
            case 7: {
                exit = 1;
                break;
            }
            default: {
                printf("Opção inválida!\n");
                break;
            }
        }
    }

    return 0;
}

void exibirLNSE(LNSE *lnse) {
    if (lnse == NULL) {
        return;
    }

    int pos = lnse->head;

    printf("\nEstado atual da LNSE (interpretação):\n\n");

    // Linha superior das caixas para cada elemento na LNSE
    while (pos != -1) {
        printf("+-----");
        pos = lnse->registers[pos].next;
    }
    printf("+\n");

    // Reinicia a posição para exibir os valores na ordem
    pos = lnse->head;
    while (pos != -1) {
        printf("| %3d ", lnse->registers[pos].value);
        pos = lnse->registers[pos].next;
    }
    printf("|\n");

    // Linha inferior das caixas
    pos = lnse->head;
    while (pos != -1) {
        printf("+-----");
        pos = lnse->registers[pos].next;
    }
    printf("+\n");

    // Reinicia a posição para exibir os índices
    pos = lnse->head;
    int i = 0;
    while (pos != -1) {
        printf("  %3d ", i++);
        pos = lnse->registers[pos].next;
    }
}
