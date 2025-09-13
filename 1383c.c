#include <stdio.h>
#include <stdlib.h>

int analiseLinha(int **matriz, int i){
    int usado[10] = {0};
    for (int j = 0; j < 9; j++) {
        int num = matriz[i][j];
        if (usado[num]) return 0;         
        usado[num] = 1;
    }
    return 1;                             
}

int analiseColuna(int **matriz, int j){
    int usado[10] = {0};
    for (int i = 0; i < 9; i++){
        int num = matriz[i][j];
        if (usado[num]) return 0;
        usado[num] = 1;
    }
    return 1;
}

int analiseBloco(int **matriz, int bi, int bj){
    int usado[10] = {0};
    for (int i = bi; i < bi + 3; i++){
        for (int j = bj; j < bj + 3; j++){
            int num = matriz[i][j];
            if (usado[num]) return 0;
            usado[num] = 1;
        }
    }
    return 1;
}

int main(){
    int k;
    scanf("%d", &k);

    for (int l = 0; l < k; l++){
        
        int **m = (int **) malloc(9 * sizeof(int *));
        for (int i = 0; i < 9; i++) {
            m[i] = (int *) malloc(9 * sizeof(int));
        }

    
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                scanf("%d", &m[i][j]);
            }
        }

        int valido = 1;
        for (int i = 0; i < 9; i++) {
            if (!analiseLinha(m, i)) {
                valido = 0;
                break;
            }
        }

        for (int j = 0; j < 9; j++) {
            if (!analiseColuna(m, j)) {
                valido = 0;
                break;
            }
        }

        for (int bi = 0; bi < 9; bi += 3){
            for (int bj = 0; bj < 9; bj += 3){
                if (!analiseBloco(m, bi, bj)) {
                    valido = 0;
                    break;
                }
            }
        }

        printf("Instancia %d\n", l+1);
        if (valido)
            printf("SIM\n");
        else
            printf("NAO\n");
        printf("\n");

        
        for (int i = 0; i < 9; i++) free(m[i]);
        free(m);
    }
    
    return 0;
}
