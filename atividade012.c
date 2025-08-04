#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

const int INF = INT_MAX;

// estrutura para a grafo com lista de adjacencia
typedef struct Grafo {
    int vertice;
    int peso;
    struct Grafo *seg;
} Grafo;


Grafo **iniciarGrafo(int vertices) {
    Grafo **grafo = (Grafo**)malloc(sizeof(Grafo*) * vertices);
    
    for (int i = 0; i < vertices; i++) {
        grafo[i] = (Grafo*)malloc(sizeof(Grafo));
        grafo[i]->vertice = i;
        grafo[i]->seg = NULL;
    }

    return grafo;
}


void append(Grafo **grafo, int origem, int destino, int peso) {
    Grafo *novo = (Grafo*)malloc(sizeof(Grafo));
    novo->vertice = destino;
    novo->peso = peso;
    novo->seg = NULL;

    Grafo *temp = grafo[origem];

    while (temp->seg != NULL && temp->seg->vertice < destino)
        temp = temp->seg;
    
    novo->seg = temp->seg;
    temp->seg = novo;
}


void caminho(Grafo **grafo, int V, int inicio, int fim, int *dist) {
    if (fim == inicio) {
        printf("%d", inicio);
        return;
    }

    // percorre todos os potenciais predecessores u
    for (int u = 0; u < V; u++) {
        for (Grafo *it = grafo[u]->seg; it; it = it->seg) {
            if (it->vertice == fim && dist[u] != INF && dist[u] + it->peso == dist[fim]) {
                // encontrou um u que tem conexao com o fim;
                caminho(grafo, V, inicio, u, dist);
                printf(" %d", fim);
                return;
            }
        }
    }

    printf("Destino nao alcancado");
}


void bellmanFord(Grafo **grafo, int vertices, int origem, int restricao, int fim) {
    int *distancia =(int*)malloc(sizeof(int) * vertices);

    // Inicializa as distâncias com infinito
    for (int i = 0; i < vertices; i++)
        distancia[i] = INF;
    distancia[origem] = 0;

    // Relaxa todas as arestas
    for (int i = 1; i <= vertices; i++) {
        for (int u = 0; u < vertices; u++) {
            Grafo *visitado = grafo[u]->seg;

            while (visitado != NULL) {
                int v = visitado->vertice;
                int peso = visitado->peso;

                if (peso <= restricao && distancia[u] != INF && distancia[u] + peso < distancia[v]) 
                    distancia[v] = distancia[u] + peso;

                visitado = visitado->seg;
            }
        }
    }

    // Verifica ciclos negativos
    for (int u = 0; u < vertices; u++) {
        Grafo *visitado = grafo[u]->seg;

        while (visitado != NULL) {
            int v = visitado->vertice;
            int peso = visitado->peso;

            if (peso <= restricao && distancia[u] != INF && distancia[u] + peso < distancia[v])
                return; // cliclo negativo detectado;

            visitado = visitado->seg;
        }
    }

    // Imprime as distâncias finais
    for (int i = 0; i < vertices; i++) {
        if (distancia[i] == INF)
            printf("INF ");
        else
            printf("%d ", distancia[i]);
    }
    printf("\n");

    // imprime o caminho até um vertice x
    caminho(grafo, vertices, origem, fim, distancia);

    free(distancia);
}


int main() {
    int vertices, arestas, inicio, restricao, fim;
    Grafo **grafo;

    scanf("%d %d", &inicio, &restricao);

    scanf("%d %d", &vertices, &arestas);

    // inicializa o grafo
    grafo = iniciarGrafo(vertices);

    //le o grafo
    for (int i = 0; i < arestas; i++) {
        int origem, destino, peso;

        scanf("%d %d %d", &origem, &destino, &peso);

        append(grafo, origem, destino, peso);
    }
    // le o vertice do fim
    scanf("%d", &fim);

    // executa o algoritmo de caminho minimo
    bellmanFord(grafo, vertices, inicio, restricao, fim);

    // libera a memoria 
    for (int i = 0; i < vertices; i++) {
        Grafo *temp = grafo[i];

        while (temp != NULL) {
            Grafo *prox = temp->seg;
            free(temp);
            temp = prox;
        }
    }
    free(grafo);

    return 0;
}
