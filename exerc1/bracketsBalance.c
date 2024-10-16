#include "bracketsBalance.h"

// ================== PARTE DA PILHA ==================
// Função para criar uma nova stack
Stack* createStack() {

    // Usaremos malloc para que a stack possa ser usada em outras funcoes e para evitar ter que retornar uma copia dela
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->top = NULL;
    stack->tamanho = 0;
    return stack;
}

// Função para criar um novo nó
Node* createNode(char data) {

    // Usaremos malloc para que o noh possa ser usada em outras funcoes e para evitar ter que retornar uma copia dele
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->next = NULL;

    return node;
}

// Função para verificar se a stack está vazia
int isStackEmpty(Stack* stack) {

    if (stack->tamanho==0){
        return 1;
    }
    else{
        return 0;
    }

    // Outras maneiras válidas
    //------------------------
    // return stack->tamanho==0;
    // return stack->top == NULL;
    //------------------------
}

// Função para adicionar um elemento no topo da stack
void push(Stack* stack, char data) {
    Node* node = createNode(data);

    // O novo noh ira apontar para o noh que era o topo antes
    node->next = stack->top;

    // Substitui o topo pelo novo noh
    stack->top = node;
    stack->tamanho++;
}

// Função para remover e retornar o elemento do topo da stack
char pop(Stack* stack) {

    if ( isStackEmpty(stack) ) {
        printf("\nStack vazia. Erro (underflow)");
        return -1;  // Erro: underflow
    }

    Node* temp = stack->top;
    int data = temp->data;

    // O novo noh sera o que estava apontado pelo noh que sera excluido
    stack->top = stack->top->next;

    // Libera o espaço de memória que foi alocado para o noh
    free(temp);

    stack->tamanho--;

    return data;
}

// Função para retornar a quantidade de elementos da stack
int size(Stack* stack) {
    return stack->tamanho;
}

// Função para retornar o topo da stack sem remover
char peekStack(Stack* stack) {

    if ( isStackEmpty(stack) ) {
        printf("\nStack vazia. Erro (underflow)");
        return -1;  // Erro: underflow
    }

    return stack->top->data;
}

// Função para limpar a stack
void clearStack(Stack* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
}

// Função para imprimir a stack
void printStack(Stack* stack) {
    Stack* auxStack = createStack();
    printf("\n[");

    // Seguindo as regras da stack, a unica forma de
    // acessar todos os seus valores, eh destruindo ela
    while ( isStackEmpty(stack)!=1 ) {
        int data = pop(stack);

        // Salva o dado na outra stack para recuperar depois
        push(auxStack, data);
        printf(" %d", data);
    }

    while ( isStackEmpty(auxStack)!=1 ) {
        int data = pop(auxStack);

        // Recupera o valor na stack original
        push(stack, data);
    }

    printf(" ]\n");

    free(auxStack);
}
// ====================================================

// ================== PARTE DA FILA ===================
// Função para criar uma nova fila
Queue* createQueue(int initSize) {

    // Usaremos malloc para que a fila possa ser usada em outras funcoes e para evitar ter que retornar uma copia dela
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    queue->data = (char *)calloc(initSize, sizeof(char));
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = initSize;
    queue->size = 0;

    return queue;
}

// Função para adicionar um elemento no final da fila
void enqueue(Queue* queue, char data) {
    if (queue->size == queue->capacity) {
        printf("\nQueue cheia. Erro (overflow)");
        return;  // Erro: overflow
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
}

// Função para remover e retornar o elemento do início da fila
char dequeue(Queue* queue) {

    if (isQueueEmpty(queue)) {
        printf("\nQueue vazia. Erro (underflow)");
        return -1;  // Erro: underflow
    }

    char data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity; // O modulo garante que o indice nao ultrapasse o tamanho da fila-
    queue->size--;

    return data;
}

// Função para retornar o início da fila sem remover
char peek(Queue* queue) {

    if (isQueueEmpty(queue)) {
        printf("\nQueue vazia. Erro (underflow)");
        return -1;  // Erro: underflow
    }

    return queue->data[queue->front];
}

// Função para verificar se a fila está vazia
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Função para imprimir a fila
void printQueue(Queue* queue) {
    printf("\n");

    for (int i = 0; i < queue->size; i++) {
        printf(" %c", queue->data[(queue->front + i) % queue->capacity]); // O modulo garante que o indice nao ultrapasse o tamanho da fila
    }

    printf("\n");
}

// Função para limpar a fila
void clearQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ATENÇÃO, A FUNÇÃO ABAIXO É APENAS PARA FACILITAR O TESTES NA MAIN()
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

// Função para converter uma string em uma fila
Queue* stringToQueue(char* string) {
    Queue* queue = createQueue(strlen(string));

    for (int i = 0; i < strlen(string); i++) {
        enqueue(queue, string[i]);
    }

    return queue;
}

// ====================================================