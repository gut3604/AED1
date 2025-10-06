#include <stdio.h>
#include <string.h>

//exercicio 1069 utilizando pilha

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // consome o '\n' após o número

    char s[1001];

    for (int i = 0; i < N; i++) {
        fgets(s, 1001, stdin);
        int len = strlen(s);
        if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';

        int diamante = 0;
        char p[1000]; // pilha para armazenar '<'
        int t = 0;    // topo da pilha

        for (int j = 0; s[j] != '\0'; j++) {
            switch (s[j]) {
                case '<':
                    p[t++] = '<'; // empilha
                    break;
                case '>':
                    if (t > 0 && p[t-1] == '<') {
                        --t;        // desempilha
                        diamante++; // formou um diamante
                    }
                    break;
                default:
                    break; // ignora '.' ou outros
            }
        }

        printf("%d\n", diamante);
    }

    return 0;
}