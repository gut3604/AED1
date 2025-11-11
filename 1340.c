#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Implementações simples das três estruturas

typedef struct {
    int dados[MAX];
    int topo;
} Pilha;

typedef struct {
    int dados[MAX];
    int ini, fim;
} Fila;

typedef struct {
    int dados[MAX];
    int tam;
} FilaPrioridade;

void push_pilha(Pilha *p, int x) {
    p->dados[++p->topo] = x;
}

int pop_pilha(Pilha *p) {
    return p->dados[p->topo--];
}

int empty_pilha(Pilha *p) {
    return p->topo < 0;
}

void push_fila(Fila *f, int x) {
    f->dados[f->fim++] = x;
}

int pop_fila(Fila *f) {
    return f->dados[f->ini++];
}

int empty_fila(Fila *f) {
    return f->ini == f->fim;
}

// Fila de prioridade (máximo sempre na frente)
void push_fp(FilaPrioridade *fp, int x) {
    fp->dados[fp->tam++] = x;
}

int pop_fp(FilaPrioridade *fp) {
    if (fp->tam == 0) return -1;
    int max_i = 0;
    for (int i = 1; i < fp->tam; i++) {
        if (fp->dados[i] > fp->dados[max_i])
            max_i = i;
    }
    int val = fp->dados[max_i];
    fp->dados[max_i] = fp->dados[--fp->tam];
    return val;
}

int empty_fp(FilaPrioridade *fp) {
    return fp->tam == 0;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        Pilha pilha = {.topo = -1};
        Fila fila = {.ini = 0, .fim = 0};
        FilaPrioridade fp = {.tam = 0};

        int eh_pilha = 1, eh_fila = 1, eh_fp = 1;

        for (int i = 0; i < n; i++) {
            int cmd, x;
            scanf("%d %d", &cmd, &x);

            if (cmd == 1) {
                push_pilha(&pilha, x);
                push_fila(&fila, x);
                push_fp(&fp, x);
            } else {
                if (!empty_pilha(&pilha)) {
                    int val = pop_pilha(&pilha);
                    if (val != x) eh_pilha = 0;
                } else eh_pilha = 0;

                if (!empty_fila(&fila)) {
                    int val = pop_fila(&fila);
                    if (val != x) eh_fila = 0;
                } else eh_fila = 0;

                if (!empty_fp(&fp)) {
                    int val = pop_fp(&fp);
                    if (val != x) eh_fp = 0;
                } else eh_fp = 0;
            }
        }

        int possiveis = eh_pilha + eh_fila + eh_fp;
        if (possiveis == 0)
            printf("impossible\n");
        else if (possiveis > 1)
            printf("not sure\n");
        else if (eh_pilha)
            printf("stack\n");
        else if (eh_fila)
            printf("queue\n");
        else
            printf("priority queue\n");
    }
    return 0;
}
