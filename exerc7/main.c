#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree.h"

int main()
{
    srand(time(NULL)); // Seed for random numbers

    Tree* tree = createTree();

    for(int i = 0; i < 10; i++)
    {
        int value = rand() % 100;
        tree->root = insert(tree->root, value);
        printf("Inserindo %d\n", value);
    }

    printf("\nPreorder: ");
    strPreorder(tree->root);

    printf("\nSoma de cada caminho: \n");
    caminhos(tree->root, 0);
}
