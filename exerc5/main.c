#include "Exercicio5.h" // Inclui o cabeçalho com as funções definidas
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Criando uma matriz esparsa
    Matriz* matriz = criarMatriz(7,7);
    int removido = 0;

    printf("Inserindo valores na matriz...\n");

    inserir(matriz, 5, 5, 10);
    inserir(matriz, 1, 5, 20);
    inserir(matriz, 5, 1, 30);
    inserir(matriz, 1, 1, 40);
    inserir(matriz, 3, 3, 50);
    inserir(matriz, 1, 3, 60);
    inserir(matriz, 3, 5, 70);
    inserir(matriz, 3, 1, 80);
    inserir(matriz, 5, 3, 90);
    inserir(matriz, 0, 0, 100);  
    inserir(matriz, 7, 7, 110);
    inserir(matriz, 0, 3, 120);
    inserir(matriz, 3, 0, 120);
    inserir(matriz, 5,2, 130);
    removido = remover(matriz, 5,3);
    inserir(matriz, 5,3, 150);
    removido = remover(matriz, 5,4);
    inserir(matriz, 7,3, 150);
    removido = remover(matriz, 0,0);
    inserir(matriz, 3,4, 170);
    removido = remover(matriz, 3,1);

    printf("------------ Primeira matriz ----------------\n");
    printf("Imprimindo apenas valores\n");
    imprimir_apenas_valores(matriz);
    printf("Imprimindo matriz inteira\n");
    imprimir(matriz);

    printf("O tamanho da matriz depois das inserções é: %d\n", matriz->size);

    float esparsidade = calculaEsparsidade(matriz);
    printf("A esparsidade da matriz é: %.2f\n", esparsidade);
    int somaInternaValor = somaInterna(matriz);
    printf("A soma interna da matriz é: %d\n", somaInternaValor);

    // testando a soma de matrizes
    Matriz* matriz2 = criarMatriz(7,7);
    inserir(matriz2, 0, 0, 5);
    inserir(matriz2, 1, 1, 10);
    inserir(matriz2, 2, 2, 15);
    inserir(matriz2, 3, 3, 20);
    inserir(matriz2, 4, 4, 25);
    inserir(matriz2, 5, 5, 30);
    inserir(matriz2, 1, 3, 35);
    inserir(matriz2, 3, 1, 40);
    inserir(matriz2, 2, 0, 45);
    inserir(matriz2, 4, 1, 50);
    inserir(matriz2, 5, 2, 55);
    printf("------------ Segunda Matriz----------------\n");
    printf("Imprimindo apenas valores\n");
    imprimir_apenas_valores(matriz2);
    printf("Imprimindo matriz inteira\n");
    imprimir(matriz2);
    
    printf("------------ Soma das Matrizes----------------\n");

    Matriz* matriz_soma = somar(matriz, matriz2);

    printf("Imprimindo apenas valores\n");
    imprimir_apenas_valores(matriz_soma);
    printf("Imprimindo matriz inteira\n");
    imprimir(matriz_soma);

    return 0;
}
