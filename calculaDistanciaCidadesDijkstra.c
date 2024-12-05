#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Aresta {
    char destino;
    int peso;
    struct Aresta* proxima;
} Aresta;

typedef struct Vertice {
    char nome;
    Aresta* arestas;
    struct Vertice* proximo;
} Vertice;

void adicionarAresta(Vertice* vertices, char origem, char destino, int peso) {
    Vertice* temp = vertices;
    while (temp && temp->nome != origem) {
        temp = temp->proximo;
    }
    if (!temp) return;
    
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = temp->arestas;
    temp->arestas = novaAresta;
}

Vertice* inicializarGrafo() {
    Vertice* vertices = NULL;
    char nomes[] = {'A', 'B', 'C', 'D', 'E'};
    for (int i = 4; i >= 0; i--) {
        Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
        novoVertice->nome = nomes[i];
        novoVertice->arestas = NULL;
        novoVertice->proximo = vertices;
        vertices = novoVertice;
    }
    adicionarAresta(vertices, 'A', 'B', 4);
    adicionarAresta(vertices, 'A', 'C', 2);
    adicionarAresta(vertices, 'A', 'D', 7);
    adicionarAresta(vertices, 'B', 'A', 4);
    adicionarAresta(vertices, 'B', 'C', 1);
    adicionarAresta(vertices, 'B', 'E', 1);
    adicionarAresta(vertices, 'C', 'A', 2);
    adicionarAresta(vertices, 'C', 'B', 1);
    adicionarAresta(vertices, 'C', 'D', 3);
    adicionarAresta(vertices, 'C', 'E', 3);
    adicionarAresta(vertices, 'D', 'A', 7);
    adicionarAresta(vertices, 'D', 'C', 3);
    adicionarAresta(vertices, 'D', 'E', 2);
    adicionarAresta(vertices, 'E', 'B', 1);
    adicionarAresta(vertices, 'E', 'C', 3);
    adicionarAresta(vertices, 'E', 'D', 2);
    return vertices;
}


int obterIndiceVertice(char* vertices, int tamanho, char vertice) {
    for (int i = 0; i < tamanho; i++) {
        if (vertices[i] == vertice) return i;
    }
    return -1;
}

// encontra o vertice menor e nao visto
char encontrarMenorDistancia(int* distancias, int* visitados, char* vertices, int tamanho) {
    int menorDistancia = INT_MAX;
    char menorVertice = '\0';
    for (int i = 0; i < tamanho; i++) {
        if (!visitados[i] && distancias[i] < menorDistancia) {
            menorDistancia = distancias[i];
            menorVertice = vertices[i];
        }
    }
    return menorVertice;
}


void dijkstra(Vertice* grafo, char inicio) {
    char vertices[] = {'A', 'B', 'C', 'D', 'E'};
    int tamanho = 5;
    int distancias[5];
    int visitados[5] = {0};
    int anteriores[5];
    for (int i = 0; i < tamanho; i++) {
        distancias[i] = INT_MAX;
        anteriores[i] = -1;
    }
    distancias[obterIndiceVertice(vertices, tamanho, inicio)] = 0;

    for (int i = 0; i < tamanho; i++) {
        char atual = encontrarMenorDistancia(distancias, visitados, vertices, tamanho);
        if (atual == '\0') break;
        int indiceAtual = obterIndiceVertice(vertices, tamanho, atual);

        visitados[indiceAtual] = 1;
        Vertice* temp = grafo;
        while (temp && temp->nome != atual) {
            temp = temp->proximo;
        }
        if (!temp) continue;

        Aresta* aresta = temp->arestas;
        while (aresta) {
            int indiceVizinho = obterIndiceVertice(vertices, tamanho, aresta->destino);
            if (!visitados[indiceVizinho] && distancias[indiceAtual] + aresta->peso < distancias[indiceVizinho]) {
                distancias[indiceVizinho] = distancias[indiceAtual] + aresta->peso;
                anteriores[indiceVizinho] = indiceAtual; 
            }
            aresta = aresta->proxima;
        }
    }

    //resultados
    printf("Distancias de %c\n", inicio);
    for (int i = 0; i < tamanho; i++) {
        printf("Ate %c: %d\n", vertices[i], distancias[i]);
    }

    //menor tempo para A ate E
    printf("\nMenor tempo para chegar de A ate E: %d\n", distancias[obterIndiceVertice(vertices, tamanho, 'E')]);
    printf("Caminho: ");
    int atual = obterIndiceVertice(vertices, tamanho, 'E');
    while (atual != -1) {
        printf("%c ", vertices[atual]);
        atual = anteriores[atual];
    }
    printf("\n");

    //menor tempo para A ate D
    printf("\nMenor tempo para chegar de A ate D: %d\n", distancias[obterIndiceVertice(vertices, tamanho, 'D')]);
    printf("Caminho: ");
    atual = obterIndiceVertice(vertices, tamanho, 'D');
    while (atual != -1) {
        printf("%c ", vertices[atual]);
        atual = anteriores[atual];
    }
    printf("\n");
}

int main() {
    Vertice* grafo = inicializarGrafo();
    char inicio = 'A';
    dijkstra(grafo, inicio);
    scanf("%s",inicio);
    return 0;
}
