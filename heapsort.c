#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *arr, int n, int i) {
    int maxi = i;
    int temp;
    int l = i * 2 + 1;
    int r = i * 2 + 2;

    if ((l < n) && (arr[l] > arr[maxi])) maxi = l;
    if ((r < n) && (arr[r] > arr[maxi])) maxi = r;

    if (maxi != i) {
        swap(arr + i, arr + maxi);
        heapify(arr, n, maxi);
    }
}

void heapSort(int *arr, int n) {
    if (n < 2) return;

    for(int i = n / 2 - 1; i > -1; i--) heapify(arr, n, i);
    
    for(int i = n - 1; i > 0; i--) {
        swap(arr, arr + i);
        heapify(arr, i, 0);
    }
}

int main(){
    int arr[13] = {1,65,243,53,6,32,634,53,35,63,325,53,5};
    heapSort(arr, 13);
    for (int i = 0; i < 13; i++) printf("%d\n", arr[i]);
}