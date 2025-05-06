#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

int main() {
    const int n = 100000;
    int* arr = new int[n];

    // Fill array with sample data
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    long sum = 0;
    double avg = 0.0;

    // Parallel Reduction
    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
        sum += arr[i];
    }

    avg = (double)sum / n;

    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;

    delete[] arr;
    return 0;
}
