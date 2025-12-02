#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    int chave;
    struct cel *esq;
    struct cel *dir;
} celula;

typedef celula *arvore;

celula *criar_novo(int x){
    celula *novo = malloc(sizeof(celula));
    novo->chave = x;
    novo->esq = novo->dir = NULL;
    return novo;
}

arvore inserir(arvore r, celula *novo){
    celula *p = r, *f;

    if (r == NULL) return novo;

    while (p != NULL){
        f = p;
        if (p->chave > novo->chave) p = p->esq;
        else p = p->dir;
    }

    if (f->chave > novo->chave) f->esq = novo;
    else f->dir = novo;

    return r;
}

void imprimir_infix(arvore r, int *primeiro) {
    if (r == NULL) return;
    imprimir_infix(r->esq, primeiro);
    if (!*primeiro) printf(" ");
    printf("%d", r->chave);
    *primeiro = 0;
    imprimir_infix(r->dir, primeiro);
}

void imprimir_prefix(arvore r, int *primeiro) {
    if (r == NULL) return;
    if (!*primeiro) printf(" ");
    printf("%d", r->chave);
    *primeiro = 0;
    imprimir_prefix(r->esq, primeiro);
    imprimir_prefix(r->dir, primeiro);
}

void imprimir_posfix(arvore r, int *primeiro) {
    if (r == NULL) return;
    imprimir_posfix(r->esq, primeiro);
    imprimir_posfix(r->dir, primeiro);
    if (!*primeiro) printf(" ");
    printf("%d", r->chave);
    *primeiro = 0;
}

int main() {
    int C; // numero de casos
    scanf("%d", &C);

    for (int caso = 1; caso <= C; caso++) {
        int N;
        scanf("%d", &N);

        arvore r = NULL;

        for (int i = 0; i < N; i++) {
            int valor;
            scanf("%d", &valor);
            r = inserir(r, criar_novo(valor));
        }

        printf("Case %d:\n", caso);

        int primeiro = 1;
        printf("Pre.: ");
        imprimir_prefix(r, &primeiro);
        printf("\n");

        primeiro = 1;
        printf("In..: ");
        imprimir_infix(r, &primeiro);
        printf("\n");

        primeiro = 1;
        printf("Post: ");
        imprimir_posfix(r, &primeiro);
        printf("\n\n");
    }

    return 0;
}
