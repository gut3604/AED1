#include <stdio.h>

#define MAX 1024

char grid[MAX][MAX];
int N, M;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void bfs(int sx, int sy) {
    static int qx[MAX * MAX];
    static int qy[MAX * MAX];
    int ini = 0, fim = 0;

    qx[fim] = sx;
    qy[fim] = sy;
    fim++;

    grid[sx][sy] = 'o'; // marca como visitado (vira preto)

    while (ini < fim) {
        int x = qx[ini];
        int y = qy[ini];
        ini++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (grid[nx][ny] == '.') {
                    grid[nx][ny] = 'o';
                    qx[fim] = nx;
                    qy[fim] = ny;
                    fim++;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%s", grid[i]);

    int cliques = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') {
                cliques++;
                bfs(i, j);
            }
        }
    }

    printf("%d\n", cliques);

    return 0;
}
