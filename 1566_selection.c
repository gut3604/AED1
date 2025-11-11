#include <stdio.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int v[n];
        for (int i = 0; i < n; i++) scanf("%d", &v[i]);
        selectionSort(v, n);
        for (int i = 0; i < n; i++) {
            if (i > 0) printf(" ");
            printf("%d", v[i]);
        }
        printf("\n");
    }
    return 0;
}
