#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v, w; } Edge;
Edge e[200000];
int parent[200000];

int find(int x){ return parent[x] == x ? x : (parent[x] = find(parent[x])); }

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n), m) {
        int total = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
            total += e[i].w;
        }

        for (int i = 0; i < m; i++) parent[i] = i;

        qsort(e, n, sizeof(Edge), cmp);

        int mst = 0;
        for (int i = 0; i < n; i++) {
            int a = find(e[i].u), b = find(e[i].v);
            if (a != b) {
                parent[a] = b;
                mst += e[i].w;
            }
        }
        printf("%d\n", total - mst);
    }
    return 0;
}
