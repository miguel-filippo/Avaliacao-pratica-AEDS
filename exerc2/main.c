#include "doubleStack.h"

int main(void) {
    // Create a double stack with a size of 10
    DoubleStack* stack = createDoubleStack(10);

    // Test pushing to head
    pushHead(stack, 1);
    pushHead(stack, 2);
    pushHead(stack, 3);

    // Test pushing to tail
    pushTail(stack, 10);
    pushTail(stack, 9);
    pushTail(stack, 8);

    // Print the stack
    printDoubleStack(stack);

    // Test popping from head
    printf("Popped from head: %d\n", popHead(stack));
    printf("Popped from head: %d\n", popHead(stack));

    // Test popping from tail
    printf("Popped from tail: %d\n", popTail(stack));
    printf("Popped from tail: %d\n", popTail(stack));

    // Print the stack again
    printDoubleStack(stack);

    // Test isFull and isEmpty
    printf("Is stack full? %s\n", isFull(stack) ? "Yes" : "No");
    printf("Is stack empty? %s\n", isEmpty(stack) ? "Yes" : "No");

    // Fill the stack completely
    pushHead(stack, 4);
    pushHead(stack, 5);
    pushHead(stack, 6);
    pushTail(stack, 7);
    pushTail(stack, 8);
    pushTail(stack, 9);
    pushHead(stack, 10);
    pushTail(stack, 11);
    pushTail(stack, 12);


    // Print the stack again
    printDoubleStack(stack);

    // Test isFull again
    printf("Is stack full? %s\n", isFull(stack) ? "Yes" : "No");

    // Free the stack
    freeDoubleStack(stack);

    return 0;
}
