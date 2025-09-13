#include <stdio.h>

int main(){
    int n, v[1000], menor, posicao;
    scanf("%d", &n);
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
    return 0;
}
