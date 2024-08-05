#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

Grafo* criarGrafo(int numVertices) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        printf("Erro: falha ao alocar memória para o grafo.\n");
        exit(EXIT_FAILURE);
    }
    grafo->numVertices = numVertices;
    grafo->vertices = (Vertice *)malloc(numVertices * sizeof(Vertice));
    if (grafo->vertices == NULL) {
        printf("Erro: falha ao alocar memória para os vértices do grafo.\n");
        free(grafo);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numVertices; i++) {
        grafo->vertices[i].valor = i + 1;
        grafo->vertices[i].listaAdj = NULL;
    }
    return grafo;
}

void destruirGrafo(Grafo *grafo) {
    if (grafo != NULL) {
        for (int i = 0; i < grafo->numVertices; i++) {
            Aresta *atual = grafo->vertices[i].listaAdj;
            while (atual != NULL) {
                Aresta *prox = atual->prox;
                free(atual);
                atual = prox;
            }
        }
        free(grafo->vertices);
        free(grafo);
    }
}

void adicionarAresta(Grafo *grafo, int origem, int destino, int peso) {
    if (origem < 1 || origem > grafo->numVertices || destino < 1 || destino > grafo->numVertices) {
        printf("Erro: vértices de origem ou destino inválidos!\n");
        return;
    }
    Aresta *novaAresta = (Aresta *)malloc(sizeof(Aresta));
    if (novaAresta == NULL) {
        printf("Erro: falha ao alocar memória para a nova aresta.\n");
        exit(EXIT_FAILURE);
    }
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->prox = grafo->vertices[origem - 1].listaAdj;
    grafo->vertices[origem - 1].listaAdj = novaAresta;
}

void imprimirGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("Vértice %d:", grafo->vertices[i].valor);
        Aresta *atual = grafo->vertices[i].listaAdj;
        while (atual != NULL) {
            printf(" (%d, %d)", atual->destino, atual->peso);
            atual = atual->prox;
        }
        printf("\n");
    }
}

