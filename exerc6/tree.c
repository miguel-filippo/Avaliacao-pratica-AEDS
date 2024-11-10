#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Node* createNode(int data){
    Node* node = (Node*) malloc( sizeof(Node) );

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Tree* createTree(){
    Tree* tree = (Tree*) malloc( sizeof(Tree) );

    tree->root = NULL;
    return tree;
};

Node* insert( Node* node, int data ){

    if (node == NULL){
        Node* newNode = createNode(data);
        return newNode;
    }

    // verifica se vai para o lado esquerdo
    if (data < node->data){
        node->left = insert(node->left, data);
    }
    // vai para o lado direito
    else{
        node->right = insert(node->right, data);
    }

    return node;
}

int search( Node* node, int data ){

    if (node == NULL){
        return 0;
    }

    if (data == node->data){
        return 1;
    }

    int achou;
    // verifica se vai para o lado esquerdo
    if (data < node->data){
        achou = search(node->left, data);
    }
    // vai para o lado direito
    else{
        achou = search(node->right, data);
    }

    return achou;

}

// Essa função é a implementação exigiada no exercício 6.
int getSubNodesQuantity(Node* node) {

    // Retorna 0 quando for nulo para nao somar nada na conta porque nao tem mais subnoh
    if (node == NULL) {
        return 0;
    }

    int leftCount = getSubNodesQuantity(node->left);  // Conta a quantidade de nohs pra esquerda
    int rightCount = getSubNodesQuantity(node->right);  // Conta a quantidade de nohs pra direita

    return 1 + leftCount + rightCount;  // Tem que somar 1 para contar o primeiro subnoh
}

Node* getMaxNode( Node* node ){

    if (node == NULL){
        return NULL;
    }

    if (node->right == NULL){
        return node;
    }

    return getMaxNode( node->right );

}

Node* getMinNode( Node* node ){

    if (node == NULL){
        return NULL;
    }

    if (node->left == NULL){
        return node;
    }

    return getMinNode( node->left );

}

Node* deleteNode( Node* node, int data,
                    char filhoSubstituto){

    if (node == NULL){
        return node;
    }

    if (data < node->data){
        node->left = deleteNode( node->left, data,
                                      filhoSubstituto);
    }
    else if( data > node->data ){
         node->right = deleteNode( node->right, data,
                                      filhoSubstituto);
    }
    else{
        // encontrou o noh que sera excluido
        if(node->left == NULL){
            Node* tempNode = node->right;
            free(node);
            return tempNode;
        }
        else if( node->right == NULL ){
            Node* tempNode = node->left;
            free(node);
            return tempNode;
        }
        else{
            // o noh possui dois filhos
            Node* tempNode;
            if( filhoSubstituto == 'D' ){
                // o menor de todos do lado direito
                tempNode = getMinNode(node->right);
                node->data = tempNode->data;
                node->right = deleteNode(node->right,
                                        tempNode->data,
                                        filhoSubstituto);
            }
            else{
                // o maior de todos do lado esquerdo
                tempNode = getMaxNode(node->left);
                node->data = tempNode->data;
                node->left = deleteNode(node->left,
                                        tempNode->data,
                                        filhoSubstituto);
            }
        }
    } // fecha o else

    return node;
}

void strPreorder(Node *node){
    if( node != NULL ){

        printf("%d ", node->data );
        strPreorder(node->left);
        strPreorder(node->right);
    }
}


// Função para percorrer a árvore em ordem
void strInorder(Node *node) {
    if (node != NULL) {

        strInorder(node->left);
        printf("%d ", node->data);
        strInorder(node->right);
    }
}

// Função para percorrer a árvore em pós-ordem
void strPostorder(Node *node) {
    if (node != NULL) {

        strPostorder(node->left);
        strPostorder(node->right);
        printf("%d ", node->data);
    }
}
