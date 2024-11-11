#include "Exercicio5.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar um novo nó
Node* criarNode(int data, int typeOfNode) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novoNode->data = data;
    novoNode->typeOfNode = typeOfNode;
    novoNode->nextColumn = NULL;
    novoNode->nextLine = NULL;
    return novoNode;
}

// Função para inicializar uma matriz
Matriz* criarMatriz(int linhaMax, int colMax) {
    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    matriz->HeadListOfLines = NULL;
    matriz->HeadListOfCol = NULL;
    matriz->LinhaMax = linhaMax;
    matriz->ColMax = colMax;
    matriz->size = 0;
    return matriz;
}

int getSize(Matriz* matriz){
    return matriz->size;
}

int isEmpty(Matriz* matriz){
    return matriz->HeadListOfLines==NULL;
}


void inserir(Matriz* matriz, int line, int col, int valor) {

    // verifica se os valores são válidos
    if (line < 0 || col < 0 || col > matriz->ColMax || line > matriz->LinhaMax || valor != (int)valor) {
        printf("Erro: Os valores de coluna e linha devem ser validos e o valor inserido deve ser um número inteiro.\n");
        return;
    }
    // verifica se o valor é zero e devemos remover o nó
    if (valor == 0) {
        int valor = remover(matriz, line, col); // Implementar a função de remoção separadamente
        return;
    }

    Node* newNode = criarNode(valor, 1); // Esse node é para lista com os valores
    // passando a linha e a coluna para o nó 
    newNode->column = col; newNode->line = line;
    
    // caso a matriz esteja vazia, cria o primeiro nó e inicializa as listas de linhas e colunas
    if (matriz->HeadListOfLines == NULL || matriz->HeadListOfCol == NULL) { // os dois só podem ser nulos simultanetamente
        Node* newNodeListOfLines = criarNode(valor, 0); // Esse node é para conter o primeiro valor da lista de linhas
        Node* newNodeListOfCols = criarNode(valor, 0); // Esse node é para conter o primeiro valor da lista de colunas
        
        // passando os nodes das listas de colunas e linhas para a matriz
        matriz->HeadListOfLines = newNodeListOfLines;
        matriz->HeadListOfCol = newNodeListOfCols;
        // setando suas respectivas linhas e colunas
        matriz->HeadListOfLines->line = line;
        matriz->HeadListOfCol->column = col;
        //passando o nó com o valor para as listas de linhas e colunas
        matriz->HeadListOfLines->nextColumn = newNode;
        matriz->HeadListOfCol->nextLine = newNode;
    
        matriz->size++;
        return;
    }
    // CASO NAO ESTEJA VAZIA

    // São as listas contendo os vetores para as listas com os valores
    Node* linhaAtual = matriz->HeadListOfLines;
    Node* colunaAtual = matriz->HeadListOfCol;

    // ----- inserção na cadeia de linhas -------- 
    // Caso o primeiro valor da primeira linha seja maior que o valor da linha onde se deseja inserir 
    if (linhaAtual->line > line){
        Node* newNodeListOfLines = criarNode(valor, 0); // Esse node é para conter o primeiro valor da lista de linhas
        newNodeListOfLines->line = line;
        newNodeListOfLines->nextLine = linhaAtual; // passando a proxima lista da linha 
        // passando o head da lista de linhas para a matriz
        matriz->HeadListOfLines = newNodeListOfLines;
        matriz->HeadListOfLines->nextColumn = newNode; // passa para a linha o novo nó com o valor;

    // Caso o primeiro valor da primeira linha não seja maior que o valor da linha onde se deseja inserir
    }else { 
        // Verifica se a proxima linha existe e se ela é menor que a linha que se deseja inserir
        while (linhaAtual->nextLine!=NULL){
            if(linhaAtual->nextLine->line<=line){ // se a proxima linha ainda é não nula e menor ou igual, passa para a proxima
                linhaAtual = linhaAtual->nextLine; 
            }else{ // se a proxima linha é maior, quebra o laço
                break;
            }
        }
        /* Casos possíveis i) a linhaAtual == line ii) a linhaAtual->nextLine é nulla && linhaAtual->line < line  
        iii) A linhaAtual->line <line && linhaAtual->nextLine->line > line */
        if (linhaAtual->line == line){// se a linha atual é igual a linha na qual se deseja inserir, vamos verificar se a coluna já existe e onde coloca-la
            // se existe a linha já se supõe que tem ao menos uma coluna
            if(linhaAtual->nextColumn->column > col){ // se a primeira coluna é maior do que col
                newNode->nextColumn = linhaAtual->nextColumn;
                linhaAtual->nextColumn = newNode;
            }
            else{ // se a primeira coluna não é maior do que col
                
                while (linhaAtual->nextColumn!=NULL){ // procura a coluna
                    if(linhaAtual->nextColumn->column <= col){
                        linhaAtual = linhaAtual->nextColumn;
                    }else{
                        break;
                    }
                }
                if (linhaAtual->column == col){ // caso no qual ponto na matriz já existe
                    linhaAtual->data = valor;
                    free(newNode); // não precisa de um novo nó 
                    return;
                }
                else if(linhaAtual->nextColumn == NULL){ // esse nó ainda não existe e é o ultimo da linha
                    linhaAtual->nextColumn = newNode;
                }
                else if (linhaAtual->nextColumn->column > col){ // nó é colocado entre os nós que ja existem
                    newNode->nextColumn = linhaAtual->nextColumn;
                    linhaAtual->nextColumn = newNode;
                }
                else{
                    printf("Houve algum problema na inserção da coluna na linha\n");
                    return;
                }

            }

        }else if (linhaAtual->nextLine == NULL){ // se a proxima linha é nulla e a linha atual é menor que line
            Node* newNodeLine = criarNode(valor, 0); // vetor da linha que será o tail da lista de linhas.
            newNodeLine->line = line; 
            linhaAtual->nextLine = newNodeLine; // linha atual tem como a proxima linha a nova linha
            newNodeLine->nextColumn = newNode; // a linha recebe o node com o valor
        }
        else if (linhaAtual->nextLine->line > line){ // se a proxima linha é maior e a linha atual é menor que line

            Node* newNodeLine = criarNode(valor, 0); // novo vetor da linha 
            newNodeLine->line = line; 
            newNodeLine->nextLine = linhaAtual->nextLine;
            linhaAtual->nextLine = newNodeLine; // linha atual tem como a proxima linha a nova linha
            newNodeLine->nextColumn = newNode; // a linha recebe o node com o valor

        }
        else{ // nenhum dos casos foi suficiente, algo deu errado.
            printf("Houve algum problema na inserção da linha\n");
            return;
        }

    }
// ----- inserção na cadeia de colunas -------- 
    // Segue a mesma lógica que a inserção na cadeia de linhas, por isso os comentários serão omitidos, para clareza do código
    
    // Se col é menor que a primeira coluna
    if (colunaAtual->column > col){ 
        Node* newNodeListOfCols = criarNode(valor, 0); 
        newNodeListOfCols->column = col;
        newNodeListOfCols->nextColumn = colunaAtual;  
        // passando o head da lista de colunas para a matriz
        matriz->HeadListOfCol = newNodeListOfCols;
        matriz->HeadListOfCol->nextLine = newNode; // passa para a coluna o novo nó com o valor;
        matriz->size++;
        return;

    // Caso o primeiro valor da primeira coluna não seja maior que o valor da coluna onde se deseja inserir
    }else { 
        while (colunaAtual->nextColumn!=NULL){
            if(colunaAtual->nextColumn->column<=col){ // se a proxima coluna ainda é não nula e menor ou igual, passa para a proxima
                colunaAtual = colunaAtual->nextColumn; 
            }else{ // se a proxima coluna é maior, quebra o laço, se for nula, também sai do laço
                break;
            }
        }
        /* Casos possíveis i) a colunaAtual == col ii) a colunaAtual->nextcoluna é nulla && colunaAtual->col < col  
        iii) A colunaAtual->coluna <col && colunaAtual->nextCol->coluna > col */
        if (colunaAtual->column == col){
            if(colunaAtual->nextLine->line > line){ // se a primeira linha é maior do que line
                newNode->nextLine = colunaAtual->nextLine;
                colunaAtual->nextLine = newNode;
                matriz->size++;
                return;
            }
            else{
                
                while (colunaAtual->nextLine!=NULL){
                    if(colunaAtual->nextLine->line <= line){
                        colunaAtual = colunaAtual->nextLine;
                    }else{
                        break;
                    }
                }
                // nunca vai ter o caso que o nó já existe, por que foi tratado
                // if (colunaAtual->line == line){ // caso no qual ponto na matriz já existe
                //     linhaAtual->data = valor;
                //     free(newNode); // não precisa de um novo nó 
                //     return;
                // }
                if(colunaAtual->nextLine == NULL){ // esse nó ainda não existe
                    colunaAtual->nextLine = newNode;
                    matriz->size++;
                    return;
                }
                else if (colunaAtual->nextLine->line > line){ // nó é colocado entre os nós que ja existem
                    newNode->nextLine = colunaAtual->nextLine;
                    colunaAtual->nextLine = newNode;
                    matriz->size++;
                    return;
                }
                else{
                    printf("Houve algum problema na inserção da linha na coluna\n");
                    return;
                }

            }
        // a coluna ainda não existe e não tem nenhuma maior que ela
        }else if (colunaAtual->nextColumn == NULL){ 
            Node* newNodeCol = criarNode(valor, 0); 
            newNodeCol->column = col; 
            colunaAtual->nextColumn = newNodeCol; // linha atual tem como a proxima linha a nova linha
            newNodeCol->nextLine = newNode; // a coluna recebe o node com o valor
            matriz->size++;
            return;
        }
        // a coluna da frente é maior que col e a de trás é menor, coloca entre elas
        else if (colunaAtual->nextColumn->column > col){ 

            Node* newNodeCol = criarNode(valor, 0); // novo vetor da coluna
            newNodeCol->column = col; 
            newNodeCol->nextColumn = colunaAtual->nextColumn;
            colunaAtual->nextColumn = newNodeCol; 
            newNodeCol->nextLine = newNode; 
            matriz->size++;
            return;
        }
        else{ // nenhum dos casos foi suficiente, algo deu errado.
            printf("Houve algum problema na inserção da coluna\n");
            return;
        }

    }    

    // Incrementa o tamanho da matriz
    matriz->size++;
    return;
}

void imprimir_apenas_valores(Matriz* matriz) {
    /*A função imprimir também faz um plot de todos os pontos da matriz que possuem valores, 
    além dos valores com seus respectivos indicies*/
    Node* Node_lines = matriz->HeadListOfLines; // Ponteiro para percorrer
    Node* Node_cols = matriz->HeadListOfCol; // Ponteiro para percorrer

    if (Node_lines == NULL || Node_cols == NULL){
        printf("A matriz está vazia\n");
        return;
    }

    while (Node_lines != NULL) {
        printf("Linha %d :    ", Node_lines->line);

        Node* current = Node_lines->nextColumn; // Ponteiro para percorrer a linha atual
        while (current != NULL) {

            printf("(i: %d, j: %d, %d)    ", current->line, current->column, current->data);
            current = current->nextColumn; // Vai para o próximo nó na mesma linha
        }
        printf("\n"); // Pula uma linha após imprimir uma linha completa
        Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    }

    // while (Node_cols != NULL) {
    //     printf("coluna:");
    //     printf("%d :    ", Node_cols->column);

    //     Node* current = Node_cols->nextLine; // Ponteiro para percorrer a linha atual
    //     while (current != NULL) {

    //         printf("(i: %d, j: %d, %d)    ", current->line, current->column, current->data);
    //         current = current->nextLine; // Vai para o próximo nó na mesma linha
    //     }
    //     printf("\n"); // Pula uma linha após imprimir uma linha completa
    //     Node_cols = Node_cols->nextColumn; // Vai para a próxima linha
    // }

    
}
// Função para buscar um valor 
int buscar(Matriz* matriz, int line, int col) {
        // verifica se os valores são válidos
    if (line < 0 || col < 0|| col > matriz->ColMax || line > matriz->LinhaMax) {
        printf("Erro: Os valores de coluna e linha devem ser naturais.\n");
        return 0;
    }

    Node* nodeAtual = matriz->HeadListOfLines; // Ponteiro para percorrer

    // percorre as linhas até encontrar a linha desejada
    while (nodeAtual != NULL ) {
        if(nodeAtual->line >= line){
            break;
        }
        nodeAtual = nodeAtual->nextLine;
    }
    // Se a linha não existir, retorna 0
    if (nodeAtual == NULL) {
        return 0;
    }else if(nodeAtual->line != line){
        return 0;
    }

    //percorre a linha até encontrar a coluna desejada
    nodeAtual = nodeAtual->nextColumn; // passa para os nós com os valores
    while (nodeAtual != NULL) {
        if(nodeAtual->column >= col){
            break;
        }
        nodeAtual = nodeAtual->nextColumn;
    }
    // Se a coluna não existir, retorna 0
    if (nodeAtual == NULL) {
        return 0;
    }
    else if (nodeAtual->column != col){
        return 0;
    }
    // Retorna o valor encontrado
    return nodeAtual->data;
}

int remover(Matriz* matriz,int line, int col){       // verifica se os valores são válidos

    if (line < 0 || col < 0 || col > matriz->ColMax || line > matriz->LinhaMax) {
        printf("Erro: Os valores de coluna e linha devem ser validos.\n");
        return 0;
    }
    if(isEmpty(matriz)){
        return 0;
    }
    if(buscar(matriz, line,col) == 0){ // se a posição já estiver vazia
        return 0;
    }
    Node* linhaAtual = matriz->HeadListOfLines; // Ponteiro para percorrer linhas
    Node* colunaAtual = matriz->HeadListOfCol; // Ponteiro para percorrer colunas

    /*É melhor tratar das conexões das linhas e colunas separadamente, depois faz a liberação da memória do nó se tudo ocorrer certo no final
    mas trata os dois separadamente, faz para um caso depois copia para o outro*/

    /*É possível remover primeiro as ligações da linha e depois da coluna, logo, trataremos os casos isoladamente*/
    /*-------------------- Remoção nas linhas ---------------------------------------------------------------------*/
    //  --------------- se está na primeira linha ------------------------------
    if(linhaAtual->line == line ){
        //se é o primeiro elemento da linha
        if(linhaAtual->nextColumn->column == col){
            // se é o unico elemento da linha
            if(linhaAtual->nextColumn->nextColumn == NULL){
                // se é o unico elemento da matriz 
                if(linhaAtual->nextLine==NULL){

                    int valor = linhaAtual->nextColumn->data;
                    free(linhaAtual->nextColumn); // libera o nó com o valor
                    free(matriz->HeadListOfLines); //  libera o head da lista de linhas
                    free(matriz->HeadListOfCol); //  libera o head da lista de colunas
                    matriz->HeadListOfLines = NULL; matriz->HeadListOfCol = NULL;
                    matriz->size--;
                    return valor;
                }
                // se existem mais elementos em outras linhas, mas essa linha será eliminada, temos que mudar o headOfLine
                else if(linhaAtual->nextLine != NULL){
                    matriz->HeadListOfLines = linhaAtual->nextLine;
                    free(linhaAtual);
                }
                else{
                    printf("Erro na remoção do primeiro elemento da primeira linha - 1");
                    return 0;
                }
            }// se não é o unico elemento da linha, só precisa mudar a referencia na lista de linhas
            else if(linhaAtual->nextColumn->nextColumn != NULL){
                //Node *Node_temp = linhaAtual->nextColumn; // não pode pois depois tem que ter remoção da coluna
                linhaAtual->nextColumn = linhaAtual->nextColumn->nextColumn; // muda a ligação da lista de linhas
                //free(Node_temp);
            }else{
                printf("Erro na remoção do primeiro elemento da primeira linha - 2");
                return 0;
            }
            
        }
        // se está na primeira linha mas não é o primeiro elemento da linha e tem outros depois dele
        else if(linhaAtual->nextColumn->nextColumn != NULL){ // se o elemento depois desse existe
            
            linhaAtual = linhaAtual->nextColumn; // ja viu que não é o primeiro elemento da lista, e sabe que o próximo dele não é nulo
            // vamos procurar a coluna do elemento que se deseja eliminar
            while (linhaAtual->nextColumn!=NULL){
                if(linhaAtual->nextColumn->column<col){ // se a proxima coluna ainda é não nula e menor, passa para a proxima
                    linhaAtual = linhaAtual->nextColumn; 
                }else{ // se a proxima coluna é maior ou igual do que onde se procura, para o laço
                    break;
                }
            }
            /* Casos possíveis i) linhaAtual != col && linhaAtual->nextColum == NULL ii) linhaAtual->nextCol->col == col 
            iii) linhaAtual->nextCol->col > col */

            if(linhaAtual->nextColumn == NULL){
                printf("O elemento não existe na matriz");
                return 0;
            }
            else if(linhaAtual->nextColumn->column == col){ // encontrou a coluna onde está 
                //Node *Node_temp = linhaAtual->nextColumn // 
                linhaAtual->nextColumn = linhaAtual->nextColumn->nextColumn; // independente se for NULL ou não
                //free(Node_temp); // não pode, ainda precisa fazer para as colunas
            }
            else if(linhaAtual->nextColumn->column > col){
                printf("O elemento não existe na matriz");
                return 0;
            }
            else{
                printf("Erro na remoção do elemento da primeira linha");
                return 0;
            }


        }
        else{ // Se não é o primeiro e não tem elemento após o primeiro, o nó não existe
            printf("O elemento não existe na matriz");
            return 0;
        }
    }
    //  ------------------------ se não está na primeira linha ------------------------------------------
    else if(linhaAtual->nextLine == NULL){ // se não tem uma próxima linha 
        printf("O elemento não existe na matriz");
        return 0;
    }
    else{ // se tem proxima linha, procura a linha linha = i
        while(linhaAtual->nextLine !=NULL){
            if(linhaAtual->nextLine->line < line){ // se a proxima linha é menor que a linha desejada, continua
                linhaAtual = linhaAtual->nextLine;
            }else{
                break;
            }
        }
            /* Casos possíveis i) linhaAtual != line && linhaAtual->nextline == NULL ii) linhaAtual->nextLine->line == line 
            iii) linhaAtual->nextLine->line > line */
        if (linhaAtual->nextLine == NULL){
            printf("O elemento não existe na matriz");
            return 0;
        }else if (linhaAtual->nextLine->line == line){ 
            //----------------- encontrou a linha, começar remoção nela  --------------------
            // lembrando que a linha que contem é linhaAtual->nextLine
            Node *linhaCorreta = linhaAtual->nextLine;
            //se é o primeiro elemento da linha
            if(linhaCorreta->nextColumn->column == col){
                // se é o unico elemento da linha, a linha desaparece
                if(linhaCorreta->nextColumn->nextColumn == NULL){
                    linhaAtual->nextLine = linhaCorreta->nextLine;
                    free(linhaCorreta); // o nó ainda não é liberado pois precisa liberar as colunas

                }// se não é o unico elemento da linha, só precisa mudar a referencia na lista de linhas
                else if(linhaCorreta->nextColumn->nextColumn != NULL){
                    linhaCorreta->nextColumn = linhaCorreta->nextColumn->nextColumn; // muda a ligação da lista de linhas
                    //free(Node_temp); // nao faz pq tem que fazer da coluna ainda
                }else{
                    printf("Erro na remoção do primeiro elemento da linha");
                    return 0;
                }   
            }// se está na linha mas não é o primeiro elemento da linha e tem outros depois dele
            else if(linhaCorreta->nextColumn->nextColumn != NULL){ // se o elemento depois desse existe
                
                linhaCorreta = linhaCorreta->nextColumn; // ja viu que não é o primeiro elemento da lista, e sabe que o próximo dele não é nulo
                // vamos procurar a coluna do elemento que se deseja eliminar
                while (linhaCorreta->nextColumn!=NULL){
                    if(linhaCorreta->nextColumn->column<col){ // se a proxima coluna ainda é não nula e menor, passa para a proxima
                        linhaCorreta = linhaCorreta->nextColumn; 
                    }else{ // se a proxima coluna é maior ou igual do que onde se procura, para o laço
                        break;
                    }
                }
                /* Casos possíveis i) linhaAtual != col && linhaAtual->nextColum == NULL ii) linhaAtual->nextCol->col == col 
                iii) linhaAtual->nextCol->col > col */

                if(linhaCorreta->nextColumn == NULL){
                    printf("O elemento não existe na matriz");
                    return 0;
                }
                else if(linhaCorreta->nextColumn->column == col){ // encontrou a coluna onde está  
                    linhaCorreta->nextColumn = linhaCorreta->nextColumn->nextColumn; // independente se for NULL ou não
                    //free(Node_temp); // não pode, ainda precisa fazer para as colunas
                }
                else if(linhaCorreta->nextColumn->column > col){
                    printf("O elemento não existe na matriz");
                    return 0;
                }
                else{
                    printf("Erro na remoção do elemento da primeira linha");
                    return 0;
                }

            }
            else{ // Se não é o primeiro e não tem elemento após o primeiro, o nó não existe
                printf("O elemento não existe na matriz");
                return 0;
            }
        }
         // --------------------- não está na matriz ----------------
        else if(linhaAtual->nextLine->line > line){ // passou e não encontrou
            printf("O elemento não existe na matriz");
            return 0;
        }
        else{ // se nenhum dos casos satisfaz, tem um erro na lógica
                printf("Erro na procura da linha onde está o elemento");
                return 0;
        }
    
    }
    /*-------------------- Remoção nas colunas ---------------------------------------------------------------------*/
    /// como é a mesma lógica da remoção nas linhas, alguns comentários serão excluídos para limpar o código
    //  --------------- se está na primeira coluna ------------------------------
    if(colunaAtual->column == col ){
        //se é o primeiro elemento da coluna
        if(colunaAtual->nextLine->line == line){
            // se é o unico elemento da coluna
            if(colunaAtual->nextLine->nextLine == NULL){
                // Existem mais elementos em outras colunas, mas essa coluna será eliminada, temos que mudar o headOfCol
                int valor = colunaAtual->nextLine->data; // é o nó com o valor 
                matriz->HeadListOfCol = colunaAtual->nextColumn;
                free(colunaAtual->nextLine); // libera o nó excluído com o valor
                free(colunaAtual); // libera a coluna excluída
                matriz->size--;
                return valor;

            }// se não é o unico elemento da coluna, só precisa mudar a referencia na lista de colunas
            else if(colunaAtual->nextLine->nextLine != NULL){
                Node *Node_temp = colunaAtual->nextLine; // nó que vai ser excluído
                int valor = colunaAtual->nextLine->data; // valor do nó excluído
                colunaAtual->nextLine = colunaAtual->nextLine->nextLine; // muda a ligação da lista de colunas
                free(Node_temp);
                matriz->size--;
                return valor;
                            
            }else{
                printf("Erro na remoção do primeiro elemento da primeira coluna");
                return 0;
            }
        }
        // se está na primeira coluna mas não é o primeiro elemento da coluna e tem outros depois dele
        else if(colunaAtual->nextLine->nextLine != NULL){ // se o elemento depois desse existe
            
            colunaAtual = colunaAtual->nextLine; // ja viu que não é o primeiro elemento da lista, e sabe que o próximo dele não é nulo
            // vamos procurar a linha do elemento que se deseja eliminar
            while (colunaAtual->nextLine!=NULL){
                if(colunaAtual->nextLine->line<line){ // se a proxima linha ainda é não nula e menor, passa para a proxima
                    colunaAtual = colunaAtual->nextLine; 
                }else{ // se a proxima linha é maior ou igual do que onde se procura, para o laço
                    break;
                }
            }
            /* Casos possíveis: i) colunaAtual->line != line && colunaAtual->nextline == NULL ii) colunaAtual->nextline->line == line 
            iii) colunaAtual->nextLine->line > line */
            // na verdade o unico caso possível é o que o elemento existe, pq os casos que não existe já foram tratados

            if(colunaAtual->nextLine == NULL){ 
                printf("O elemento não existe na matriz - exclusão colunas -1");
                return 0;
            }
            else if(colunaAtual->nextLine->line == line){ // encontrou a coluna onde está 
                Node *Node_temp = colunaAtual->nextLine; 
                colunaAtual->nextLine = colunaAtual->nextLine->nextLine; // independente se for NULL ou não
                int valor  =  Node_temp->data;
                free(Node_temp);
                matriz->size--; 
                return valor;
            }
            else if(colunaAtual->nextLine->line > line){
                printf("O elemento não existe na matriz - exclusão colunas -2");
                return 0;
            }
            else{
                printf("Erro na remoção do elemento da primeira coluna");
                return 0;
            }


        }
        else{ // Se não é o primeiro e não tem elemento após o primeiro, o nó não existe
            printf("O elemento não existe na matriz - exclusão colunas - 3");
            return 0;
        }
    }
    //  ------------------------ se não está na primeira coluna ------------------------------------------
    else if(colunaAtual->nextColumn == NULL){ // se não tem uma próxima coluna 
        printf("O elemento não existe na matriz - 3");
        return 0;
    }
    else{ // se tem proxima coluna, procura a coluna, tq coluna = j
        while(colunaAtual->nextColumn !=NULL){
            if(colunaAtual->nextColumn->column < col){ // se a proxima coluna é menor que a linha desejada, continua
                colunaAtual = colunaAtual->nextColumn;
            }else{
                break;
            }
        }
            /* Casos possíveis i) linhaAtual != line && linhaAtual->nextline == NULL ii) linhaAtual->nextLine->line == line 
            iii) linhaAtual->nextLine->line > line */
            // na verdade só o caso em que existe deve acontecer, pq foi tratado isso pela procura por linha
        if (colunaAtual->nextColumn == NULL){
            printf("O elemento não existe na matriz - 4");
            return 0;
        }else if (colunaAtual->nextColumn->column == col){ 
            //----------------- encontrou a coluna, começar remoção nela  --------------------
            Node *colunaCorreta = colunaAtual->nextColumn;
            //se é o primeiro elemento da coluna
            if(colunaCorreta->nextLine->line == line){
                // se é o unico elemento da coluna
                if(colunaCorreta->nextLine->nextLine == NULL){ /////////////
                    colunaAtual->nextColumn = colunaCorreta->nextColumn;
                    int valor = colunaCorreta->nextLine->data; //  valor do nó 
                    free(colunaCorreta->nextLine); // libera o nó
                    free(colunaCorreta); // libera a coluna
                    matriz->size--;
                    return valor; 

                }// se não é o unico elemento da coluna, só precisa mudar a referencia na lista de colunas
                else if(colunaCorreta->nextLine->nextLine != NULL){
                    Node *Node_temp = colunaCorreta->nextLine;
                    int valor = Node_temp->data;
                    colunaCorreta->nextLine = colunaCorreta->nextLine->nextLine; // muda a ligação da lista de linhas
                    free(Node_temp); // libera a memória do nó 
                    matriz->size--;
                    return valor;
                }else{
                    printf("Erro na remoção do primeiro elemento da coluna");
                    return 0;
                }   
            }// se está na coluna mas não é o primeiro elemento da coluna e tem outros depois dele
            else if(colunaCorreta->nextLine->nextLine != NULL){ // se o elemento depois desse existe
                
                colunaCorreta = colunaCorreta->nextLine; // ja viu que não é o primeiro elemento da lista, e sabe que o próximo dele não é nulo
                // vamos procurar a linha do elemento que se deseja eliminar
                while (colunaCorreta->nextLine!=NULL){
                    if(colunaCorreta->nextLine->line<line){ // se a proxima linha ainda é não nula e menor, passa para a proxima
                        colunaCorreta = colunaCorreta->nextLine; 
                    }else{ // se a proxima linha é maior ou igual do que onde se procura, para o laço
                        break;
                    }
                }
                /* Casos possíveis i) linhaAtual != col && linhaAtual->nextColum == NULL ii) linhaAtual->nextCol->col == col 
                iii) linhaAtual->nextCol->col > col */
                // na verdade apenas o caso que existe é possível, pq os de não existência ja foram tratados pela remoção nas linhas

                if(colunaCorreta->nextLine == NULL){
                    printf("O elemento não existe na matriz - 5");
                    return 0;
                }
                else if(colunaCorreta->nextLine->line == line){ // encontrou a linha onde está 
                    Node *Node_temp = colunaCorreta->nextLine;
                    int valor  = Node_temp->data; 
                    colunaCorreta->nextLine = colunaCorreta->nextLine->nextLine; // independente se for NULL ou não
                    free(Node_temp);
                    matriz->size--;
                    return valor; 
                }
                else if(colunaCorreta->nextLine->line > line){
                    printf("O elemento não existe na matriz - 6");
                    return 0;
                }
                else{
                    printf("Erro na remoção do elemento nas colunas");
                    return 0;
                }

            }
            else{ // Se não é o primeiro e não tem elemento após o primeiro, o nó não existe
                printf("O elemento não existe na matriz - 7");
                return 0;
            }
        }
         // --------------------- não está na matriz ----------------
        else if(colunaAtual->nextColumn->column > col){ // passou e não encontrou
            printf("O elemento não existe na matriz - 8");
            return 0;
        }
        else{ // se nenhum dos casos satisfaz, tem um erro na lógica
                printf("Erro na procura da coluna onde está o elemento");
                return 0;
        }
    }
}

int somaInterna(Matriz* matriz) {

    Node* Node_lines = matriz->HeadListOfLines; // Ponteiro para percorrer
    Node* Node_cols = matriz->HeadListOfCol; // Ponteiro para percorrer
    int soma = 0;

    if (Node_lines == NULL || Node_cols == NULL){
        printf("A matriz está vazia\n");
        return 0;
    }
    while (Node_lines != NULL) {
        
        Node* current = Node_lines->nextColumn; // Ponteiro para percorrer a linha atual
        while (current != NULL) {

            soma = soma + current->data;
            current = current->nextColumn; // Vai para o próximo nó na mesma linha
        }
        Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    }
    return soma;
}

float calculaEsparsidade(Matriz* matriz){
    float esparsidade = 0;

    Node* Node_lines = matriz->HeadListOfLines; // Ponteiro para percorrer
    Node* Node_cols = matriz->HeadListOfCol; // Ponteiro para percorrer

    if (Node_lines == NULL || Node_cols == NULL){
        printf("A matriz está vazia\n");
        return 0;
    }

    while (Node_lines->nextLine != NULL) {
        Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    }

    while (Node_cols->nextColumn != NULL) {
        Node_cols = Node_cols->nextColumn; // Vai para a próxima coluna
    }    

    int maxCol = Node_cols->column;
    int maxLine = Node_lines->line;
    int tamanhoDaMatriz = maxCol*maxLine;
    float numeroDeZeros =(float)(tamanhoDaMatriz - matriz->size);
    esparsidade = (float)numeroDeZeros/((float)tamanhoDaMatriz);

    return esparsidade;
}

Matriz* somar(Matriz* matriz1, Matriz* matriz2){

/* -------------------Primeiro vamos encontrar o tamanho das matrizes e verificar se elas tem o mesmo tamanho-------------*/
 //------------- matriz 1 -------------
    Node* Node_lines = matriz1->HeadListOfLines; // Ponteiro para percorrer
    Node* Node_cols = matriz1->HeadListOfCol; // Ponteiro para percorrer

    if (Node_lines == NULL || Node_cols == NULL){
        printf("A matriz1 está vazia\n");
        return NULL;
    }

    // while (Node_lines->nextLine != NULL) {
    //     Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    // }

    // while (Node_cols->nextColumn != NULL) {
    //     Node_cols = Node_cols->nextColumn; // Vai para a próxima coluna
    // }    

    int maxCol1 = matriz1->ColMax;
    int maxLine1 = matriz1->LinhaMax; 
 //------------- matriz 2 -------------
    Node_lines = matriz2->HeadListOfLines; // Ponteiro para percorrer
    Node_cols = matriz2->HeadListOfCol; // Ponteiro para percorrer

    if (Node_lines == NULL || Node_cols == NULL){
        printf("A matriz2 está vazia\n");
        return NULL;
    }
    // while (Node_lines->nextLine != NULL) {
    //     Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    // }
    // while (Node_cols->nextColumn != NULL) {
    //     Node_cols = Node_cols->nextColumn; // Vai para a próxima coluna
    // }    
    int maxCol2 = matriz2->ColMax;
    int maxLine2 = matriz2->LinhaMax; 

    if (maxLine1 != maxLine2 || maxCol1 != maxCol2){
        printf("As matrizes tem tamanhos diferentes");
        return 0;
    }
/* ------------ Se as matrizes tem tamanhos iguais, vamos percorrer a primeira matriz, procurando os valores não nulos e 
adicionando na nova matriz, cada vez que fazemos isso, verificamos se na segunda matriz existe um valor não nulo na mesma
posição. Se existir, adicionamos na nova matriz a soma dos valores não nulos das duas matrizes, e removemos o valor 
dessa posição da segunda matriz. Depois de ter percorrido completamente a primeira matriz, percorremos a segunda matriz
adicionando os valores remanescentes, que estão em posições que não existem na primeira matriz -----------*/

    Matriz* matriz_soma = criarMatriz(maxLine1,maxCol1);

    Node_lines = matriz1->HeadListOfLines; // Ponteiro para percorrer
    Node_cols = matriz1->HeadListOfCol; // Ponteiro para percorrer

    int dado1 = 0;
    int dado2 = 0;
    // Percorrendo a primeira matriz e verificando se existem valores na mesma posição na matriz2
    while (Node_lines != NULL) {

        Node* current = Node_lines->nextColumn; // Ponteiro para percorrer a linha atual
        while (current != NULL) {

            dado1 = current->data;
            dado2 = remover(matriz2,current->line, current->column);

            inserir(matriz_soma,current->line, current->column, dado1+dado2);
    
            current = current->nextColumn; // Vai para o próximo nó na mesma linha
        }
        Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    }
    
    // Percorrendo a segunda matriz e adicionando os valores remanescentes
    Node_lines = matriz2->HeadListOfLines; // Ponteiro para percorrer
    Node_cols = matriz2->HeadListOfCol; // Ponteiro para percorrer
    dado2 = 0;

    while (Node_lines != NULL) {

        Node* current = Node_lines->nextColumn; // Ponteiro para percorrer a linha atual
        while (current != NULL) {

            inserir(matriz_soma,current->line, current->column, current->data);    
            current = current->nextColumn; // Vai para o próximo nó na mesma linha
        }
        Node_lines = Node_lines->nextLine; // Vai para a próxima linha
    }    
    return matriz_soma;
}

void imprimir(Matriz* matriz) {
    // Imprime os índices das colunas

    Node* Node_lines = matriz->HeadListOfLines; // Ponteiro para percorrer
    Node* Node_cols = matriz->HeadListOfCol; // Ponteiro para percorrer

    printf("     "); // Espaço inicial para alinhar com os índices das linhas
    for (int col = 0; col <= matriz->ColMax; col++) {
        printf("%4d", col);
    }
    printf("\n");

    // Imprime uma linha de separadores
    printf("     ");
    for (int col = 0; col <= matriz->ColMax; col++) {
        printf("----");
    }
    printf("\n");

    // Imprime as linhas da matriz
    for (int linha = 0; linha <= matriz->LinhaMax; linha++) {
        // Imprime o índice da linha
        printf("%4d|", linha);

        for (int coluna = 0; coluna <= matriz->ColMax; coluna++) {
            // Busca o valor na matriz, imprimindo zero caso não exista
            int valor = buscar(matriz, linha, coluna);
            printf("%4d", valor);
        }
        printf("\n");
    }
}