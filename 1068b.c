#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de nó da pilha (lista encadeada)
typedef struct No {
    char dado;
    struct No *prox;
} No;

// Função para empilhar
void push(No **topo, char valor) {
    No *novo = (No *) malloc(sizeof(No));
    novo->dado = valor;
    novo->prox = *topo;
    *topo = novo;
}

// Função para desempilhar
int pop(No **topo) {
    if (*topo == NULL) return 0; // pilha vazia
    No *temp = *topo;
    *topo = (*topo)->prox;
    free(temp);
    return 1; // sucesso
}

// Função para liberar toda a pilha (caso sobre algo)
void liberar_pilha(No **topo) {
    while (*topo != NULL) {
        No *temp = *topo;
        *topo = (*topo)->prox;
        free(temp);
    }
}

int main() {
    char expr[1001]; // expressão de até 1000 caracteres

    // Lê até o fim do arquivo (EOF)
    while (fgets(expr, sizeof(expr), stdin)) {
        No *topo = NULL;
        int correta = 1;

        for (int i = 0; expr[i] != '\0'; i++) {
            if (expr[i] == '(') {
                push(&topo, '(');
            } else if (expr[i] == ')') {
                if (!pop(&topo)) { // tentativa de desempilhar vazia
                    correta = 0;
                    break;
                }
            }
        }

        // Se sobrou algo na pilha, está incorreta
        if (topo != NULL) correta = 0;

        if (correta)
            printf("correct\n");
        else
            printf("incorrect\n");

        liberar_pilha(&topo); // evita vazamento de memória
    }

    return 0;
}
