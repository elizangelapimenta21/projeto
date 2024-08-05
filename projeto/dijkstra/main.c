#include <stdio.h>
#include<stdlib.h>
#include "grafo.h"

//Dado a distancia o vertice e o número de vertices que ele está conectado calcula a menor distancia
int encontrarMenorDistancia(int *distancia, int *visitado, int numVertices) {
    int minDistancia = __INT_MAX__;
    int minIndice = -1;
    for (int i = 0; i < numVertices; i++) {
        if (visitado[i] == 0 && distancia[i] < minDistancia) {
            minDistancia = distancia[i];
            minIndice = i;
        }
    }
    return minIndice;
}

// Esse é o Algoritmo de Dijkstra reponsável por encontrar o caminho mais curto em um grafo
void dijkstra(Grafo *grafo, int origem, int destino) {
    int numVertices = grafo->numVertices;
    int *distancia = (int *)malloc(numVertices * sizeof(int));
    int *visitado = (int *)calloc(numVertices, sizeof(int));
    int *anterior = (int *)malloc(numVertices * sizeof(int));

    if (distancia == NULL || visitado == NULL || anterior == NULL) {
        printf("Erro: falha ao alocar memória para o algoritmo de Dijkstra.\n");
        exit(0);
    }

    for (int i = 0; i < numVertices; i++) {
        distancia[i] = __INT_MAX__;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    distancia[origem - 1] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int minIndice = encontrarMenorDistancia(distancia, visitado, numVertices);
        if (minIndice == -1) {
            break; // Se cair aqui é pq todos os vertices já foram visitados
        }
        visitado[minIndice] = 1;

        // Nessa parte eu to atualiando as distâncias dos vertices adjacentes ao vertice atual
        for (Aresta *a = grafo->vertices[minIndice].listaAdj; a != NULL; a = a->prox) {
            int destinoAtual = a->destino - 1;
            int pesoAtual = a->peso;

            if (!visitado[destinoAtual] && distancia[minIndice] != __INT_MAX__ && distancia[minIndice] + pesoAtual < distancia[destinoAtual]) {
                distancia[destinoAtual] = distancia[minIndice] + pesoAtual;
                anterior[destinoAtual] = minIndice;
            }
        }
    }
    //Quando chego aqui eu já sei quem é o caminho mais curto e qual foi distancia 
    //total que eu percorri
    printf("Caminho mais curto de %d para %d: ", origem, destino);
    int atual = destino - 1;
    while (atual != -1) {
        printf("%d ", atual + 1);
        atual = anterior[atual];
    }
    printf("\nDistância total: %d\n", distancia[destino - 1]);

    free(distancia);
    free(visitado);
    free(anterior);
}




int main() {

    //Le os dados do arquivo que foi baixado do site
    FILE *fp = fopen("grafo.txt", "r");
    Grafo *grafo = criarGrafo(270000);
    char linha[100];


    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

     while (fgets(linha, sizeof(linha), fp)) {
        int valor1, valor2, valor3;

        sscanf(linha, "%d %d %d", &valor1, &valor2, &valor3);
        adicionarAresta(grafo, valor1, valor2, valor3);

    }
    //Uma vez criado o grafo com base nas informações do arquivo a função abaixo calcula
    //o caminho mínimo entre dois pontos
    dijkstra(grafo, 1, 2);

    //Responsavel por desalocar a memoria 
    destruirGrafo(grafo);

    return 0;
}