#include "listaDuplamenteEncadeada.h"

#include <stdio.h>
#include <stdlib.h>

// Função para ordenar a lista em ordem decrescente
void ordenar(Lista* lista) {
    if (lista->ordenado == 1) {
        return;
    }
    Node* temp = lista->head;
    while (temp != NULL) {
        Node* temp2 = temp->next;
        while (temp2 != NULL) {
            if (temp->data < temp2->data) {
                int aux = temp->data;
                temp->data = temp2->data;
                temp2->data = aux;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    lista->ordenado = 1;
}


// Função para criar um novo nó
Node* criarNode(int data) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novoNode->data = data;
    novoNode->next = NULL;
    novoNode->prev = NULL;
    return novoNode;
}

// Função para inicializar uma lista duplamente ligada
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
    lista->ordenado = 1;
    return lista;
}

int getSize(Lista* lista){
    return lista->size;
}

int isEmpty(Lista* lista){
    return getSize(lista)==0;

    // return lista->head == NULL
}

void insertHead(Lista* lista, int data){

    Node* newNode = criarNode(data);

    if (getSize(lista)==0){
        lista->head = newNode;
        lista->tail = newNode;
    }
    else{
        newNode->next = lista->head;
        lista->head->prev = newNode;
        lista->head = newNode;
        lista->ordenado = 0;
    }

    lista->size++;
}

void insertTail(Lista* lista, int data){

    if( isEmpty(lista) ){
        insertHead(lista, data);
    }
    else{
        lista->ordenado = 0;

        Node* newNode = criarNode(data);

        newNode->prev = lista->tail;
        lista->tail->next = newNode;

        lista->tail = newNode;

        lista->size++;
    }
}

void insert(Lista* lista, int data, int position){

    if(position <= getSize(lista)){

        if(position==0){
            insertHead(lista, data);
        }
        else if( position==getSize(lista) ){
            insertTail(lista, data);
        }
        else{

            Node* newNode = criarNode(data);

            Node* auxNode = lista->head;
            for(int i=0; i<position-1; i++){
                auxNode = auxNode->next;
            }

            newNode->prev = auxNode;
            newNode->next = auxNode->next;

            auxNode->next->prev = newNode;
            auxNode->next = newNode;

            lista->size++;

        }

    }

}

// Função para remover um elemento da lista
void removeHead(Lista* lista){

    if ( isEmpty(lista) ){
        printf("Erro. Underflow!");
        return;
    }

    Node* nodeRemover = lista->head;

    if ( getSize(lista)==1 ){
        lista->tail = NULL;
        lista->head = NULL;
    }
    else{
        lista->head = nodeRemover->next;
        lista->head->prev = NULL;
    }

    lista->size--;

    free(nodeRemover);
}

void removeTail(Lista* lista){

    if ( isEmpty(lista) ){
        printf("Erro. Underflow!");
        return;
    }

    Node* nodeRemover = lista->tail;

    if ( getSize(lista)==1 ){
        lista->tail = NULL;
        lista->head = NULL;
    }
    else{
         lista->tail = nodeRemover->prev;
         lista->tail->next = NULL;
    }

    lista->size--;

    free(nodeRemover);// limpa o ponteiro da memória
}

void removeNode(Lista* lista, int position){

    if ( isEmpty(lista) ){
        printf("Erro. Underflow!");
        return;
    }

    if ( (position < 0 ) || (position >= getSize(lista)) ){
        printf("Posição inválida!");
        return;
    }

    // se é o primeiro nó
    if (position == 0){
        removeHead(lista);
        return;
    }

    // se é o último nó
    if (position == getSize(lista) - 1){
        removeTail(lista);
        return;
    }

    Node* tempNode = lista->head;
    int i=0;
    while( tempNode!=NULL ){

        if (i==position){

            tempNode->prev->next = tempNode->next;

            tempNode->next->prev = tempNode->prev;

            break;
        }

        tempNode = tempNode->next;
        i++;
    }

    lista->size--;
    free(tempNode);

}

int buscaLinear(Lista* lista, int data){
    Node* tempNode = lista->head;
    int i=0;
    while( tempNode!=NULL ){
        if (tempNode->data == data){
            return i;
        }
        tempNode = tempNode->next;
        i++;
    }
    return -1;
}

Node* acharMeio(Node* left, Node* right) {

    if ( left == NULL ) return NULL;

    Node* rapido = left;
    Node* lento  = left;

    while ( rapido != right && rapido->next != right ) {
        rapido = rapido->next->next;
        lento  = lento->next;
    }

    return lento;

}

Node* buscaBinaria(Node* left, Node* right, int target) {

    if ( left == NULL  ) return NULL;

    Node* middle = acharMeio(left, right);

    if ( middle->data == target ) {
        return middle;

    } else if ( middle->data < target ) {
        return buscaBinaria(middle->next, right, target);

    } else {
        return buscaBinaria(left, middle->prev, target);
    }

}

int busca(Lista* lista, int target) {
    if ( lista->ordenado ){

        printf("Busca realizada usando busca binaria.\n");
        return buscaLinear(lista, (buscaBinaria(lista->head, lista->tail, target))->data);
    }
    printf("Busca feita usando busca linear.\n");
    return buscaLinear(lista, target);
}

void clear(Lista* lista){
    Node* tempNode = lista->head;
    //int tamanho = getSize(lista);
    //for(int i=0; i<tamanho; i++){
    //    removeHead(lista);
    //}

    while( getSize(lista)>0 ){
        removeHead(lista);
    }
}

void printLista(Lista* lista){
    Node* nohAtual = lista->head;

    if( getSize(lista)==0 ){
        printf("\n[]");
        return;
    }

    printf("\n[");
    while( nohAtual->next!=NULL ){
        printf(" %d ", nohAtual->data);
        nohAtual = nohAtual->next;
    }

    // imprime o último noh
    printf(" %d ", nohAtual->data);

    printf("]");
}
