#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 510
#define INF 1000000000

int adj[MAX][MAX];
int n, m, q;

int dijkstra(int src, int dst) {
    int dist[MAX], vis[MAX];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = 0;
    }
    dist[src] = 0;

    for (;;) {
        int u = -1, best = INF;

        // pegar o não visitado com menor distância
        for (int i = 1; i <= n; i++) {
            if (!vis[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        vis[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (adj[u][v] < INF && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    return dist[dst];
}

int main() {
    while (1) {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;

        // inicializar matriz
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                adj[i][j] = INF;

        // ler arestas
        for (int i = 0; i < m; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);

            if (adj[y][x] < INF) {
                // reciprocidade → vira custo 0 em ambos sentidos
                adj[x][y] = 0;
                adj[y][x] = 0;
            } else {
                adj[x][y] = h;
            }
        }

        scanf("%d", &q);

        while (q--) {
            int o, d;
            scanf("%d %d", &o, &d);

            int result = dijkstra(o, d);

            if (result == INF)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", result);
        }

        printf("\n");
    }

    return 0;
}
