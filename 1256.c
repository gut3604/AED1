#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int m, c;
        scanf("%d %d", &m, &c);

        int table[m][c];
        int size[m];
        for (int i = 0; i < m; i++) size[i] = 0;

        for (int i = 0; i < c; i++) {
            int x;
            scanf("%d", &x);
            int h = x % m;
            table[h][size[h]++] = x;
        }

        for (int i = 0; i < m; i++) {
            printf("%d -> ", i);
            for (int j = 0; j < size[i]; j++)
                printf("%d -> ", table[i][j]);
            printf("\\\n");
        }
        if (t) printf("\n");
    }
    return 0;
}
