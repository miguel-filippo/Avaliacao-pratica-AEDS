#include "./bracketsBalance.h"

int verificaBalanceamento(Queue* filaPrincipal, Stack* pilhaAuxiliar) {
    // Cria um vetor auxiliar para guardar os elementos da fila
    char vetorAuxiliar[filaPrincipal->size];

    // Copia os elementos da fila para o vetor auxiliar
    for (int i = 0; i < filaPrincipal->size; i++) {
        vetorAuxiliar[i] = (filaPrincipal->data[(filaPrincipal->front + i) % filaPrincipal->capacity]);
    }

    int balanceado = 1;

    // Verifica se os brackets estão balanceados
    while (!isQueueEmpty(filaPrincipal)) {
        char elemento = dequeue(filaPrincipal);

        // Se o elemento for um bracket de abertura, adiciona na pilha
        if (elemento == '(' || elemento == '[' || elemento == '{') {
            push(pilhaAuxiliar, elemento);
        } 

        // Se o elemento for um bracket de fechamento, verifica se o topo da pilha é um bracket de abertura correspondente
        else {
            if (isStackEmpty(pilhaAuxiliar)) {
                balanceado = 0;
            }

            else {
                char topo = pop(pilhaAuxiliar);

                if (elemento == ')' && topo != '(') {
                    balanceado = 0;
                } else if (elemento == ']' && topo != '[') {
                    balanceado = 0;
                } else if (elemento == '}' && topo != '{') {
                    balanceado = 0;
                }
            }
        }
    }

    // Transfere os elementos do vetor auxiliar de volta para a fila para manter a ordem original  
    for(int i = 0; i < filaPrincipal->capacity; i++) {
        enqueue(filaPrincipal, vetorAuxiliar[i]);
    }

    return balanceado;
}

// Função para testar a função verificaBalanceamento()
void testa_verificaBalanceamento() {
    // Declaração das strings de teste
    char *test1 = "))(}{][][{}))()]})";
    char *test2 = "{[()]}";
    char *test3 = "{{[[(())]]}}";
    char *test4 = "{[}";


    // Conversão das strings para filas
    Queue* test1Queue = stringToQueue(test1);
    Queue* test2Queue = stringToQueue(test2);
    Queue* test3Queue = stringToQueue(test3);
    Queue* test4Queue = stringToQueue(test4);


    // Cria a pilha auxiliar
    Stack* pilhaAuxiliar = createStack();

    // Imprime as filas antes de chamar a função
    printf("=========Antes dos testes=========\n");
    printf("Fila 1: ");
    printQueue(test1Queue);
    printf("Fila 2: ");
    printQueue(test2Queue);
    printf("Fila 3: ");
    printQueue(test3Queue);
    printf("Fila 4: ");
    printQueue(test4Queue);
    printf("==================================\n");

    print("\n");
    
    // Chama a função e imprime o resultado dos testes
    printf("Test 1: %s - %s\n", test1, bracketsBalance(test1Queue, pilhaAuxiliar) ? "Balanced" : "Not Balanced");
    printf("Test 2: %s - %s\n", test2, bracketsBalance(test2Queue, pilhaAuxiliar) ? "Balanced" : "Not Balanced");
    printf("Test 3: %s - %s\n", test3, bracketsBalance(test3Queue, pilhaAuxiliar) ? "Balanced" : "Not Balanced");
    printf("Test 4: %s - %s\n", test4, bracketsBalance(test4Queue, pilhaAuxiliar) ? "Balanced" : "Not Balanced");

    print("\n");

    // Imprime as filas depois de chamar a função
    printf("=========Depois dos testes=========\n");
    printf("Fila 1: ");
    printQueue(test1Queue);
    printf("Fila 2: ");
    printQueue(test2Queue);
    printf("Fila 3: ");
    printQueue(test3Queue);
    printf("Fila 4: ");
    printQueue(test4Queue);
    printf("==================================\n");

    // Limpa as filas e a pilha
    clearStack(pilhaAuxiliar);

    free(test1Queue->data);
    free(test2Queue->data);
    free(test3Queue->data);
    free(test4Queue->data);

    free(test1Queue);
    free(test2Queue);
    free(test3Queue);
    free(test4Queue);

    free(pilhaAuxiliar);
}

int main() {
    testa_bracketsBalance();
    return 0;
}