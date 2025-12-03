#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXC 10005
#define MAXV 50005
#define INF 2000000000

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXV * 2];
int head[MAXC];
int edge_count;

typedef struct {
    int node, cost, parity;
} State;

typedef struct {
    State heap[MAXV * 4];
    int size;
} MinHeap;

void heap_swap(State *a, State *b) {
    State t = *a; *a = *b; *b = t;
}

void heap_push(MinHeap *h, State st) {
    h->heap[++h->size] = st;
    int i = h->size;
    while (i > 1 && h->heap[i].cost < h->heap[i/2].cost) {
        heap_swap(&h->heap[i], &h->heap[i/2]);
        i /= 2;
    }
}

State heap_pop(MinHeap *h) {
    State ret = h->heap[1];
    h->heap[1] = h->heap[h->size--];

    int i = 1;
    while (1) {
        int l = i * 2, r = l + 1, small = i;
        if (l <= h->size && h->heap[l].cost < h->heap[small].cost) small = l;
        if (r <= h->size && h->heap[r].cost < h->heap[small].cost) small = r;
        if (small == i) break;
        heap_swap(&h->heap[i], &h->heap[small]);
        i = small;
    }
    return ret;
}

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

long long dist[MAXC][2];
int used[MAXC][2];

long long dijkstra(int C) {
    for (int i = 1; i <= C; i++) {
        dist[i][0] = dist[i][1] = INF;
        used[i][0] = used[i][1] = 0;
    }

    MinHeap h; 
    h.size = 0;

    dist[1][0] = 0;
    heap_push(&h, (State){1, 0, 0}); // cidade 1, custo 0, par de pedágios

    while (h.size > 0) {
        State s = heap_pop(&h);
        int u = s.node;
        int p = s.parity;

        if (used[u][p]) continue;
        used[u][p] = 1;

        if (u == C && p == 0) return dist[u][0];

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].v;
            int w = edges[e].w;
            int np = p ^ 1; // troca par ↔ ímpar

            if (!used[v][np] && dist[u][p] + w < dist[v][np]) {
                dist[v][np] = dist[u][p] + w;
                heap_push(&h, (State){v, dist[v][np], np});
            }
        }
    }

    return -1;
}

int main() {
    int C, V;

    while (scanf("%d %d", &C, &V) == 2) {
        edge_count = 0;
        for (int i = 1; i <= C; i++) head[i] = -1;

        for (int i = 0; i < V; i++) {
            int a, b, g;
            scanf("%d %d %d", &a, &b, &g);
            add_edge(a, b, g);
            add_edge(b, a, g);
        }

        long long ans = dijkstra(C);
        printf("%lld\n", ans);
    }

    return 0;
}
