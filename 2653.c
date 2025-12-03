#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000005

char* jewels[MAX];
int count = 0;

// Função de comparação para qsort
int cmpstr(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    char buffer[1000005];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // remove newline
        size_t len = strlen(buffer);
        if (buffer[len-1] == '\n') buffer[len-1] = '\0';

        // aloca string
        jewels[count] = (char*)malloc(len);
        strcpy(jewels[count], buffer);
        count++;
    }

    // ordena todas as strings
    qsort(jewels, count, sizeof(char*), cmpstr);

    // conta distintos
    int distinct = 0;
    for (int i = 0; i < count; i++) {
        if (i == 0 || strcmp(jewels[i], jewels[i-1]) != 0)
            distinct++;
    }

    printf("%d\n", distinct);

    // libera memória
    for (int i = 0; i < count; i++) free(jewels[i]);

    return 0;
}
