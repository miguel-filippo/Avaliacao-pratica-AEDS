#include <stdio.h>
#include <stdlib.h>

#include "listaDuplamenteEncadeada.h"

int main()
{

    Lista* lista = criarLista();

    for (int i=0; i<10; i++){
        insert(lista, i, i);
    }

    printLista(lista);
    printf("\n");

    insert(lista, 11, 4);
    printf("\nNumero 11 adicionado no index 4.");
    printLista(lista);
    printf("\n");

    printf("Buscando numero 11.\n");
    printf("Index do numero 11: %d\n", busca(lista, 11));

    ordenar(lista);
    printf("\nLista foi ordenada.");
    printLista(lista);
    printf("\n");

    printf("Buscando numero 5.\n");
    printf("Index do numero 5: %d\n", busca(lista, 5));

    return 0;
}
