#include <stdio.h>
#include <string.h>

int contdiamantes (char s[]){
    int i, abriu = 0, fechou = 0, diamantes = 0;
    for (i=0; s[i]!= '\0'; i++){
        if (s[i] == '<'){
            abriu ++;
        }
        else if(s[i] == '>'){
            if(abriu > 0){
                diamantes++;
                abriu --;
            }
        }
     
    }
    return diamantes;

}







int main() {
    int i, N, resultado;
    char s[1000];

    scanf("%d", &N);
    getchar(); // consome o '\n' que sobra do scanf

    for(i=0; i< N; i++){
        
        fgets(s, 1000, stdin);
        
        // retirar o '\n' no final da linha, se existir
        int tamanho = strlen(s);
        if (tamanho > 0 && s[tamanho - 1] == '\n') {
            s[tamanho - 1] = '\0';
        }
        
        resultado = contdiamantes(s);
        printf("%d\n", resultado);   
    }
    
    return 0;
}