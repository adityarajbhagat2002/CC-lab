#include <stdio.h>
#include <stdlib.h>

void max_min(int arr[], int n) {
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    printf("Max value: %d\n", max);
    printf("Min value: %d\n", min);
}

void min_min(int arr[], int n) {
    int min1, min2;
    if (arr[0] < arr[1]) {
        min1 = arr[0];
        min2 = arr[1];
    } else {
        min1 = arr[1];
        min2 = arr[0];
    }
    for (int i = 2; i < n; i++) {
        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }
    printf("Min value: %d\n", min1);
    printf("Second min value: %d\n", min2);
}

int main() {
    int arr[] = {3, 9, 2, 7, 4, 6, 1, 8, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // max-min algorithm
    printf("Using max-min algorithm:\n");
    max_min(arr, n);
    
    // min-min algorithm
    printf("\nUsing min-min algorithm:\n");
    min_min(arr, n);

    return 0;
}
