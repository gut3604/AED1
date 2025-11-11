#include <stdio.h>

#define CAP 100

int tamanho(int ini, int fim) {
    if (fim >= ini) return fim - ini;
    return CAP - ini + fim;
}

int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        int fila[CAP];
        int ini = 0, fim = 0;

        for (int i = 1; i <= n; ++i) {
            fila[fim] = i;
            fim = (fim + 1) % CAP;
        }

        int descartadas[CAP];
        int qtd_desc = 0;

        while (tamanho(ini, fim) > 1) {
            // descarta a primeira
            descartadas[qtd_desc++] = fila[ini];
            ini = (ini + 1) % CAP;

            // move a próxima carta pro fim
            if (tamanho(ini, fim) >= 1) {
                fila[fim] = fila[ini];
                fim = (fim + 1) % CAP;
                ini = (ini + 1) % CAP;
            }
        }

        printf("Discarded cards:");
        if (qtd_desc > 0) {
            printf(" ");
            int i;
            for (i = 0; i < qtd_desc; ++i) {
                printf("%d", descartadas[i]);
                if (i < qtd_desc - 1) printf(", ");
            }
        }
        printf("\n");

        int restante = (tamanho(ini, fim) == 1) ? fila[ini] : 0;
        printf("Remaining card: %d\n", restante);
    }
    return 0;
}
