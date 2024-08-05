#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int valor;
    Aresta *listaAdj;
} Vertice;

typedef struct {
    Vertice *vertices;
    int numVertices;
} Grafo;

Grafo* criarGrafo(int numVertices);

void destruirGrafo(Grafo *grafo);

void adicionarAresta(Grafo *grafo, int origem, int destino, int peso);

void imprimirGrafo(Grafo *grafo);


#endif /* GRAFO_H */
