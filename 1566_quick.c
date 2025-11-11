#include <stdio.h>

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        int tmp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tmp;

        int p = i + 1;
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
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
        quickSort(v, 0, n - 1);
        for (int i = 0; i < n; i++) {
            if (i > 0) printf(" ");
            printf("%d", v[i]);
        }
        printf("\n");
    }
    return 0;
}
