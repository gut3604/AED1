#include <stdio.h>

#define MAXN 260
#define MAXM 300000
#define INF 1000000000

int head[MAXN], to[MAXM], w[MAXM], nxt[MAXM];
int dist[MAXN], vis[MAXN];
int edges;

void addEdge(int u, int v, int c) {
    to[edges] = v;
    w[edges] = c;
    nxt[edges] = head[u];
    head[u] = edges++;
}

int main() {
    int N, M, C, K;
    while (1) {
        scanf("%d %d %d %d", &N, &M, &C, &K);
        if (N == 0 && M == 0 && C == 0 && K == 0)
            break;

        edges = 0;
        for (int i = 0; i < N; i++)
            head[i] = -1;

        for (int i = 0; i < M; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);
            addEdge(u, v, p);
            addEdge(v, u, p);
        }

        // Inicia distâncias
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
            vis[i] = 0;
        }

        dist[K] = 0;

        // Dijkstra tradicional (O(N²))
        for (;;) {
            int u = -1, best = INF;

            // Escolhe o não visitado com menor dist
            for (int i = 0; i < N; i++) {
                if (!vis[i] && dist[i] < best) {
                    best = dist[i];
                    u = i;
                }
            }

            if (u == -1) break;
            vis[u] = 1;
            if (u == C - 1) break;

            if (u < C) {
                // Dentro da rota: pode ir somente para u+1
                int target = u + 1;

                for (int e = head[u]; e != -1; e = nxt[e]) {
                    if (to[e] == target) {
                        int v = target;
                        int nd = dist[u] + w[e];
                        if (nd < dist[v]) dist[v] = nd;
                    }
                }
            } else {
                // Fora da rota: todas as arestas são permitidas
                for (int e = head[u]; e != -1; e = nxt[e]) {
                    int v = to[e];
                    int nd = dist[u] + w[e];
                    if (nd < dist[v]) dist[v] = nd;
                }
            }
        }

        printf("%d\n", dist[C-1]);
    }

    return 0;
}
