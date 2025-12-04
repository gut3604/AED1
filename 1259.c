#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *esq, *dir;
} Node;

/* cria novo nó */
Node* novoNo(int v){
    Node* n = malloc(sizeof(Node));
    n->val = v;
    n->esq = n->dir = NULL;
    return n;
}

/* insere na BST normal (crescente) */
Node* inserirNormal(Node* r, int v){
    if(!r) return novoNo(v);
    if(v < r->val) r->esq = inserirNormal(r->esq, v);
    else r->dir = inserirNormal(r->dir, v);
    return r;
}

/* insere na BST invertida (para imprimir decrescente) */
Node* inserirInvertida(Node* r, int v){
    if(!r) return novoNo(v);
    if(v > r->val) r->esq = inserirInvertida(r->esq, v);  // maior vai pra esquerda
    else r->dir = inserirInvertida(r->dir, v);            // menor vai pra direita
    return r;
}

/* in-ordem normal (crescente) */
void imprimirIn(Node* r){
    if(!r) return;
    imprimirIn(r->esq);
    printf("%d\n", r->val);
    imprimirIn(r->dir);
}

/* in-ordem na árvore invertida (já imprime em ordem decrescente) */
void imprimirInInvertida(Node* r){
    if(!r) return;
    imprimirInInvertida(r->esq);
    printf("%d\n", r->val);
    imprimirInInvertida(r->dir);
}

/* libera árvore */
void liberar(Node* r){
    if(!r) return;
    liberar(r->esq);
    liberar(r->dir);
    free(r);
}

int main(void){
    int n, x;

    scanf("%d", &n);

    Node *pares = NULL;
    Node *impares = NULL;

    while(n--){
        scanf("%d", &x);

        if(x % 2 == 0)
            pares = inserirNormal(pares, x);
        else
            impares = inserirInvertida(impares, x);
    }

    /* imprime pares crescente */
    imprimirIn(pares);

    /* imprime ímpares decrescente (graças à árvore invertida) */
    imprimirInInvertida(impares);

    liberar(pares);
    liberar(impares);

    return 0;
}
