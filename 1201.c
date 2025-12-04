#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da Estrutura
typedef struct no {
    int chave;
    struct no *esq;
    struct no *dir;
} no;

// Variável global para controlar os espaços na impressão
int primeiro = 1;

// --- INSERÇÃO ---
no* insere(no* r, int v) {
    if (r == NULL) {
        no* novo = (no*)malloc(sizeof(no));
        novo->chave = v;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (v < r->chave)
        r->esq = insere(r->esq, v);
    else if (v > r->chave)
        r->dir = insere(r->dir, v);
    
    return r;
}

// --- BUSCA (Para a função P) ---
no* busca(no* r, int v) {
    if (r == NULL) return NULL;
    if (r->chave == v) return r;
    
    if (v < r->chave)
        return busca(r->esq, v);
    else
        return busca(r->dir, v);
}

// --- AUXILIAR: Acha o Maior da Esquerda (Antecessor) ---
no* maximo(no* r) {
    while (r->dir != NULL) {
        r = r->dir;
    }
    return r;
}

// --- REMOÇÃO ---
no* remover(no* r, int v) {
    if (r == NULL) return NULL;

    if (v < r->chave) {
        r->esq = remover(r->esq, v);
    } 
    else if (v > r->chave) {
        r->dir = remover(r->dir, v);
    } 
    else {
        // ACHOU O NÓ (r->chave == v)
        
        // Caso 1: Sem filhos (Folha)
        if (r->esq == NULL && r->dir == NULL) {
            free(r);
            return NULL;
        }
        // Caso 2: Só filho na direita
        else if (r->esq == NULL) {
            no* temp = r->dir;
            free(r);
            return temp;
        }
        // Caso 3: Só filho na esquerda
        else if (r->dir == NULL) {
            no* temp = r->esq;
            free(r);
            return temp;
        }
        // Caso 4: Dois filhos (O "Difícil")
        else {
            // Acha o maior valor da subárvore esquerda
            no* temp = maximo(r->esq);
            
            // Copia o valor dele para cá (Clonagem)
            r->chave = temp->chave;
            
            // Remove o nó duplicado lá embaixo
            r->esq = remover(r->esq, temp->chave);
        }
    }
    return r;
}

// --- PERCURSOS ---

void prefixa(no* r) {
    if (r != NULL) {
        if (primeiro) {
            printf("%d", r->chave);
            primeiro = 0;
        } else {
            printf(" %d", r->chave);
        }
        prefixa(r->esq);
        prefixa(r->dir);
    }
}

void infixa(no* r) {
    if (r != NULL) {
        infixa(r->esq);
        if (primeiro) {
            printf("%d", r->chave);
            primeiro = 0;
        } else {
            printf(" %d", r->chave);
        }
        infixa(r->dir);
    }
}

void posfixa(no* r) {
    if (r != NULL) {
        posfixa(r->esq);
        posfixa(r->dir);
        if (primeiro) {
            printf("%d", r->chave);
            primeiro = 0;
        } else {
            printf(" %d", r->chave);
        }
    }
}

// --- MAIN ---
int main() {
    no* raiz = NULL;
    char comando[20];
    int n;

    // Loop até acabar o arquivo (EOF)
    while (scanf("%s", comando) != EOF) {
        
        if (strcmp(comando, "I") == 0) {
            scanf("%d", &n);
            raiz = insere(raiz, n);
        } 
        else if (strcmp(comando, "R") == 0) {
            scanf("%d", &n);
            raiz = remover(raiz, n);
        } 
        else if (strcmp(comando, "P") == 0) {
            scanf("%d", &n);
            if (busca(raiz, n)) 
                printf("%d existe\n", n);
            else 
                printf("%d nao existe\n", n);
        } 
        else if (strcmp(comando, "PREFIXA") == 0) {
            primeiro = 1; // Reseta flag de espaço
            prefixa(raiz);
            printf("\n");
        } 
        else if (strcmp(comando, "INFIXA") == 0) {
            primeiro = 1;
            infixa(raiz);
            printf("\n");
        } 
        else if (strcmp(comando, "POSFIXA") == 0) {
            primeiro = 1;
            posfixa(raiz);
            printf("\n");
        }
    }

    return 0;
}
