#include "doubleStack.h"

int main(void) {
    // Criar uma pilha dupla com tamanho de 10
    DoubleStack* stack = createDoubleStack(10);

    // Teste de push na base
    pushHead(stack, 1);
    pushHead(stack, 2);
    pushHead(stack, 3);

    // Teste de push no topo
    pushTail(stack, 10);
    pushTail(stack, 9);
    pushTail(stack, 8);

    // Imprimir a pilha
    printDoubleStack(stack);

    // Teste de pop da base
    printf("Removido da base: %d\n", popHead(stack));
    printf("Removido da base: %d\n", popHead(stack));

    // Teste de pop do topo
    printf("Removido do topo: %d\n", popTail(stack));
    printf("Removido do topo: %d\n", popTail(stack));

    // Imprimir a pilha novamente
    printDoubleStack(stack);

    // Teste de isFull e isEmpty
    printf("A pilha esta cheia? %s\n", isFull(stack) ? "Sim" : "Nao");
    printf("A pilha esta vazia? %s\n", isEmpty(stack) ? "Sim" : "Nao");

    // Preencher a pilha completamente
    for (int i = 4 ; i <= 12 ; i++) {
        pushHead(stack, i);
        printf("Inserido na base: %d\n", i);
    }

    // Imprimir a pilha novamente
    printDoubleStack(stack);

    // Teste de isFull novamente
    printf("A pilha esta cheia? %s\n", isFull(stack) ? "Sim" : "Nao");

    // Liberar a pilha
    freeDoubleStack(stack);

    return 0;
}
