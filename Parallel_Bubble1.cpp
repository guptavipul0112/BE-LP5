#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i)
        for (int j = 0; j < n-i-1; ++j)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

// Parallel Bubble Sort (Odd-Even Transposition)
void parallelBubbleSort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int phase = i % 2;
        #pragma omp parallel for
        for (int j = phase; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Utility to copy array
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; ++i)
        dest[i] = source[i];
}

int main() {
    const int n = 10000;
    int arr[n], seqArr[n], parArr[n];

    // Fill with random data
    srand(time(0));
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 10000;

    copyArray(arr, seqArr, n);
    copyArray(arr, parArr, n);

    // Measure Sequential Sort Time
    double start = omp_get_wtime();
    sequentialBubbleSort(seqArr, n);
    double end = omp_get_wtime();
    cout << "Sequential Time: " << end - start << " seconds\n";

    // Measure Parallel Sort Time
    start = omp_get_wtime();
    parallelBubbleSort(parArr, n);
    end = omp_get_wtime();
    cout << "Parallel Time: " << end - start << " seconds\n";

    return 0;
}
