#include <stdio.h>
#include <stdlib.h>

#define MAXN_SMALL 105
#define MAXN_LARGE 10005

typedef struct Node {
    int v;
    struct Node* next;
} Node;

Node* adj[MAXN_LARGE];
int visited[MAXN_LARGE];
int graph[MAXN_SMALL][MAXN_SMALL];
int N, M;
int hasCycle;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void freeGraph() {
    for (int i = 1; i <= N; i++) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        adj[i] = NULL;
    }
}

void dfs_list(int u) {
    if (hasCycle) return;
    visited[u] = 1;
    for (Node* cur = adj[u]; cur != NULL; cur = cur->next) {
        int v = cur->v;
        if (visited[v] == 0) dfs_list(v);
        else if (visited[v] == 1) {
            hasCycle = 1;
            return;
        }
    }
    visited[u] = 2;
}

void dfs_matrix(int u) {
    if (hasCycle) return;
    visited[u] = 1;
    for (int v = 1; v <= N; v++) {
        if (graph[u][v]) {
            if (visited[v] == 0) dfs_matrix(v);
            else if (visited[v] == 1) {
                hasCycle = 1;
                return;
            }
        }
    }
    visited[u] = 2;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &N, &M);
        hasCycle = 0;

        if (N <= 100) {  // matriz
            for (int i = 1; i <= N; i++) {
                visited[i] = 0;
                for (int j = 1; j <= N; j++) graph[i][j] = 0;
            }
            for (int i = 0; i < M; i++) {
                int A, B;
                scanf("%d %d", &A, &B);
                graph[A][B] = 1;
            }
            for (int i = 1; i <= N; i++)
                if (visited[i] == 0) dfs_matrix(i);
        } else {  // lista encadeada
            for (int i = 1; i <= N; i++) {
                adj[i] = NULL;
                visited[i] = 0;
            }
            for (int i = 0; i < M; i++) {
                int A, B;
                scanf("%d %d", &A, &B);
                addEdge(A, B);
            }
            for (int i = 1; i <= N; i++)
                if (visited[i] == 0) dfs_list(i);
        }

        printf(hasCycle ? "SIM\n" : "NAO\n");

        if (N > 100) freeGraph();
    }

    return 0;
}
