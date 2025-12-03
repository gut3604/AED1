#include <stdio.h>
#include <string.h>

int reverse(int x) {
    int r = 0;
    while (x > 0) {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

int bfs(int a, int b) {
    int queue[20000], dist[20000];
    int front = 0, back = 0;

    memset(dist, -1, sizeof(dist));

    queue[back++] = a;
    dist[a] = 0;

    while (front < back) {
        int u = queue[front++];

        if (u == b) return dist[u];

        // operação 1 → u + 1
        if (u + 1 <= 10000 && dist[u + 1] == -1) {
            dist[u + 1] = dist[u] + 1;
            queue[back++] = u + 1;
        }

        // operação 2 → reverse(u)
        int v = reverse(u);
        if (v <= 10000 && dist[v] == -1) {
            dist[v] = dist[u] + 1;
            queue[back++] = v;
        }
    }

    return -1;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", bfs(a, b));
    }

    return 0;
}
