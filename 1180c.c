#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, *v, menor, posicao;
    
    scanf("%d", &n);
    
    v = (int *) malloc(n * sizeof(int));
    if(v == NULL){
        printf("Erro de alocacao dinamica\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++){
        scanf("%d", v + i); 
        if (i == 0){
            menor = *(v + i);
            posicao = i;
        }
        else if (*(v + i) < menor){
            menor = *(v + i);
            posicao = i;
        }
    }
    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);
    
    free(v);

    return 0;

}