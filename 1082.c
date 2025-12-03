#include <stdio.h>
#include <string.h>

#define MAX 27

int adj[MAX][MAX];
int visited[MAX];
int n, e;

// marca componente usando DFS recursivo e acumula vértices em 'list'
void dfs_collect(int v, int list[], int *sz) {
    visited[v] = 1;
    list[(*sz)++] = v;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i])
            dfs_collect(i, list, sz);
    }
}

// simples insertion sort (n <= 26, então é OK)
void sort_ints(int arr[], int sz) {
    for (int i = 1; i < sz; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    for (int caso = 1; caso <= t; caso++) {
        scanf("%d %d", &n, &e);
        memset(adj, 0, sizeof(adj));
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < e; i++) {
            char a, b;
            // lê dois chars (com espaço possível antes)
            scanf(" %c %c", &a, &b);
            int x = a - 'a';
            int y = b - 'a';
            adj[x][y] = adj[y][x] = 1;
        }

        printf("Case #%d:\n", caso);

        int components = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int list[MAX];
                int sz = 0;
                dfs_collect(i, list, &sz);

                // ordenar os vértices do componente em ordem crescente
                sort_ints(list, sz);

                // imprimir no formato pedido: a,b,c,
                for (int k = 0; k < sz; k++) {
                    printf("%c,", list[k] + 'a');
                }
                printf("\n");
                components++;
            }
        }

        printf("%d connected components\n\n", components);
    }

    return 0;
}
