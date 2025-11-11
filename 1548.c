#include <stdio.h>

void ordenar_decrescente(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vetor[j] > vetor[i]) {
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}

int main() {
    int casos;
    scanf("%d", &casos);

    while (casos--) {
        int qtd_alunos;
        scanf("%d", &qtd_alunos);

        int notas_original[qtd_alunos];
        int notas_ordenadas[qtd_alunos];

        // Lê as notas e copia para outro vetor
        for (int i = 0; i < qtd_alunos; i++) {
            scanf("%d", &notas_original[i]);
            notas_ordenadas[i] = notas_original[i];
        }

        // Ordena o vetor auxiliar em ordem decrescente
        ordenar_decrescente(notas_ordenadas, qtd_alunos);

        // Conta quantos alunos não mudaram de posição
        int cont = 0;
        for (int i = 0; i < qtd_alunos; i++) {
            if (notas_original[i] == notas_ordenadas[i])
                cont++;
        }

        printf("%d\n", cont);
    }

    return 0;
}
