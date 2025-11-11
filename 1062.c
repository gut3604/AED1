#include <stdio.h>

int main() {
    int qtd_vagoes;

    while (scanf("%d", &qtd_vagoes) && qtd_vagoes != 0) {
        while (1) {
            int ordem_desejada[qtd_vagoes];
            if (scanf("%d", &ordem_desejada[0]) != 1) return 0;

            // Se o primeiro número for 0, termina este caso
            if (ordem_desejada[0] == 0) {
                printf("\n");
                break;
            }

            // Lê o resto da sequência desejada
            for (int i = 1; i < qtd_vagoes; i++)
                scanf("%d", &ordem_desejada[i]);

            int pilha[qtd_vagoes];
            int topo = -1;
            int proximo = 1; // próximo vagão que vai entrar na estação
            int possivel = 1;

            // Processa a sequência desejada
            for (int i = 0; i < qtd_vagoes; i++) {
                int desejado = ordem_desejada[i];

                // Empilha enquanto o topo não for o vagão desejado
                while (proximo <= qtd_vagoes && (topo == -1 || pilha[topo] != desejado)) {
                    pilha[++topo] = proximo++;
                }

                // Se o topo for o vagão desejado, desempilha
                if (pilha[topo] == desejado) {
                    topo--;
                } else {
                    possivel = 0;
                    break;
                }
            }

            if (possivel)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }

    return 0;
}
