#include <stdio.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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
        insertionSort(v, n);
        for (int i = 0; i < n; i++) {
            if (i > 0) printf(" ");
            printf("%d", v[i]);
        }
        printf("\n");
    }
    return 0;
}
