#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

typedef struct Node {
    int v;
    struct Node* next;
} Node;

Node* adj[MAXN];
int visited[MAXN];
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

void dfs(int u) {
    if (hasCycle) return;
    visited[u] = 1; // visitando
    for (Node* cur = adj[u]; cur != NULL; cur = cur->next) {
        int v = cur->v;
        if (visited[v] == 0) {
            dfs(v);
        } else if (visited[v] == 1) {
            hasCycle = 1; // ciclo encontrado
            return;
        }
    }
    visited[u] = 2; // visitado
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d", &N, &M);
        
        // inicializa grafo e visitados
        for (int i = 1; i <= N; i++) {
            adj[i] = NULL;
            visited[i] = 0;
        }
        hasCycle = 0;
        
        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            addEdge(A, B);
        }
        
        // percorre todos os nós
        for (int i = 1; i <= N; i++) {
            if (visited[i] == 0) {
                dfs(i);
            }
        }
        
        if (hasCycle)
            printf("SIM\n");
        else
            printf("NAO\n");
        
        freeGraph();
    }
    
    return 0;
}
