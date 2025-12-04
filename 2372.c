#include <stdio.h>
#include <stdlib.h>

#define MAX 105
#define INF 100000000 // Um valor alto seguro (cuidado com overflow se usar INT_MAX)

int dist[MAX][MAX]; // Matriz de distâncias
int N, M;

// Função para retornar o menor entre dois números
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Função para retornar o maior entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int u, v, w;

    // Leitura: N cidades, M estradas
    scanf("%d %d", &N, &M);

    // 1. Inicializa a matriz
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) dist[i][j] = 0;   // Distância pra si mesmo é 0
            else dist[i][j] = INF;        // O resto começa como infinito
        }
    }

    // 2. Lê as arestas (Grafo não direcionado: vai e volta)
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &u, &v, &w);
        // Cuidado: pode haver múltiplas estradas entre duas cidades, pega a menor
        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;
        }
    }

    // 3. O ALGORITMO DE FLOYD-WARSHALL
    // Testa todas as cidades 'k' como intermediárias
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Se passar por K for melhor que o caminho atual, atualiza
                // Verifica se dist[i][k] e dist[k][j] não são INF para evitar somar lixo
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 4. Lógica da Reunião (Minimax)
    int menor_maior_distancia = INF;

    // Para cada cidade candidata a sediar 'i'
    for (int i = 0; i < N; i++) {
        int maior_distancia_para_i = 0;
        
        // Verifica qual amigo vai demorar mais para chegar em 'i'
        for (int j = 0; j < N; j++) {
            maior_distancia_para_i = max(maior_distancia_para_i, dist[i][j]);
        }
        
        // Queremos a cidade onde esse "pior caso" seja o menor possível
        menor_maior_distancia = min(menor_maior_distancia, maior_distancia_para_i);
    }

    printf("%d\n", menor_maior_distancia);

    return 0;
}
