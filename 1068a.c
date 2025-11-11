#include <stdio.h>
#include <string.h>

#define MAX 1000

int main() {
    char expr[MAX + 1];  // expressão de até 1000 caracteres

    // Lê até o fim do arquivo (EOF)
    while (fgets(expr, sizeof(expr), stdin)) {
        int pilha[MAX];
        int topo = -1; // pilha vazia
        int correta = 1; // assume correta até achar erro

        for (int i = 0; expr[i] != '\0'; i++) {
            if (expr[i] == '(') {
                // empilha
                pilha[++topo] = '(';
            } else if (expr[i] == ')') {
                // precisa ter um '(' correspondente
                if (topo >= 0) {
                    topo--; // desempilha
                } else {
                    correta = 0; // parêntese fechando sem abrir
                    break;
                }
            }
        }

        // Se sobrou algo na pilha, também é incorreto
        if (topo != -1) correta = 0;

        if (correta)
            printf("correct\n");
        else
            printf("incorrect\n");
    }

    return 0;
}
