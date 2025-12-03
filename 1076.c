#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV 55
#define INF 1000000000

int V, A;
int grau[MAXV];
int adj[MAXV][MAXV];      // matriz de adjacência (0/1) usada para BFS
int dist[MAXV][MAXV];     // distâncias entre nós (número de arestas no menor caminho)

int impares[MAXV], qtdImpar;
int memo[1<<20];          // DP por bitmask (suporta até 20 ímpares)
int mascaraFinal;

// BFS que retorna a distância mínima (em arestas) entre s e t num grafo não ponderado.
// Retorna INF se t for inacessível a partir de s.
int bfs_dist(int s, int t) {
    if (s == t) return 0;
    int fila[MAXV], ini = 0, fim = 0;
    int vis[MAXV] = {0};
    int d[MAXV];
    for (int i = 0; i < V; i++) d[i] = INF;

    fila[fim++] = s;
    vis[s] = 1;
    d[s] = 0;

    while (ini < fim) {
        int u = fila[ini++];
        for (int v = 0; v < V; v++) {
            if (adj[u][v] && !vis[v]) {
                vis[v] = 1;
                d[v] = d[u] + 1;
                if (v == t) return d[v];
                fila[fim++] = v;
            }
        }
    }
    return INF;
}

// Preenche a matriz dist[][] com distâncias (BFS de cada vértice)
void calcula_todas_distancias() {
    for (int s = 0; s < V; s++) {
        int fila[MAXV], ini = 0, fim = 0;
        int vis[MAXV] = {0};
        int d[MAXV];
        for (int i = 0; i < V; i++) d[i] = INF;

        fila[fim++] = s;
        vis[s] = 1;
        d[s] = 0;

        while (ini < fim) {
            int u = fila[ini++];
            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !vis[v]) {
                    vis[v] = 1;
                    d[v] = d[u] + 1;
                    fila[fim++] = v;
                }
            }
        }
        for (int i = 0; i < V; i++) dist[s][i] = d[i];
    }
}

// DP por bitmask: emparelha os vértices ímpares com custo mínimo usando dist[][].
// mask indica quais índices em 'impares[]' já foram pareados.
int dp(int mask) {
    if (mask == mascaraFinal) return 0;
    if (memo[mask] != -1) return memo[mask];

    int melhor = INF;

    // encontra o primeiro ímpar não pareado
    int i;
    for (i = 0; i < qtdImpar; i++)
        if (!(mask & (1 << i)))
            break;

    // emparelha i com algum j > i
    for (int j = i + 1; j < qtdImpar; j++) {
        if (!(mask & (1 << j))) {
            int novaMask = mask | (1 << i) | (1 << j);
            int u = impares[i], v = impares[j];
            int custo = dist[u][v];
            if (custo >= INF) continue; // não alcançável (instância inválida)
            int cand = custo + dp(novaMask);
            if (cand < melhor) melhor = cand;
        }
    }

    return memo[mask] = melhor;
}

// Emparelhamento guloso como fallback quando qtdImpar > 20
int emparelhamento_guloso() {
    int usado[MAXV] = {0};
    int restante = qtdImpar;
    int custoTotal = 0;
    while (restante > 0) {
        int bi = -1, bj = -1, best = INF;
        for (int i = 0; i < qtdImpar; i++) if (!usado[i]) {
            for (int j = i + 1; j < qtdImpar; j++) if (!usado[j]) {
                int c = dist[ impares[i] ][ impares[j] ];
                if (c < best) { best = c; bi = i; bj = j; }
            }
        }
        if (bi == -1) break; // nada mais a parear
        usado[bi] = usado[bj] = 1;
        restante -= 2;
        if (best >= INF) return INF; // impossível
        custoTotal += best;
    }
    return custoTotal;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int inicio;
        scanf("%d", &inicio);
        scanf("%d %d", &V, &A);

        // limpa estruturas
        for (int i = 0; i < V; i++) {
            grau[i] = 0;
            for (int j = 0; j < V; j++) adj[i][j] = 0;
        }

        // lê as arestas (podem existir arestas duplicadas; para grau contamos todas,
        // para BFS usamos grafo simples — adj[][] = 1)
        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            grau[u]++; grau[v]++;
            adj[u][v] = adj[v][u] = 1;
        }

        // coleta vértices de grau ímpar
        qtdImpar = 0;
        for (int i = 0; i < V; i++) {
            if (grau[i] % 2 != 0) {
                impares[qtdImpar++] = i;
            }
        }

        // calcula todas as distâncias necessárias
        calcula_todas_distancias();

        int resposta;
        if (qtdImpar == 0) {
            // já existe circuito euleriano: basta percorrer cada aresta uma vez
            resposta = A;
        } else {
            // se poucos ímpares, usamos DP por bitmask (exato)
            if (qtdImpar <= 20) {
                int lim = 1 << qtdImpar;
                for (int i = 0; i < lim; i++) memo[i] = -1;
                mascaraFinal = (1 << qtdImpar) - 1;
                int extra = dp(0);
                // se extra for INF, algo está errado (componentes desconexas), mas somamos mesmo assim
                if (extra >= INF) resposta = -1; // sinaliza erro (não ocorre nos testes válidos)
                else resposta = A + extra;
            } else {
                // fallback guloso (apenas para evitar estouro). Em instâncias do problema raramente usado.
                int extra = emparelhamento_guloso();
                if (extra >= INF) resposta = -1;
                else resposta = A + extra;
            }
        }

        // se deterimamos -1 (impossível), imprimimos A (fallback) — mas em instâncias válidas não acontece.
        if (resposta < 0) printf("%d\n", A);
        else printf("%d\n", resposta);
    }

    return 0;
}
