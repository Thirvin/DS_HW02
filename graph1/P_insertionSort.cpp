#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>

using namespace std;
using namespace chrono;

// Sequential Insertion Sort
void insertionSortSequential(vector<int>& arr, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Parallelized Insertion Sort
int now = 0;
void parallelInsertionSort(vector<int>& arr, int start, int end, int threshold) {
    if (end - start <= threshold) {
        insertionSortSequential(arr, start, end);
    } else {
        int middle = (start + end) / 2;
		now ++;
        thread t1(parallelInsertionSort, ref(arr), start, middle, threshold);
		now ++;
        thread t2(parallelInsertionSort, ref(arr), middle + 1, end, threshold);

        t1.join();
        t2.join();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <max_n>" << endl;
        return 1;
    }

    int max_n = stoi(argv[1]);

    for (int exp = 10; exp <= max_n; ++exp) {
        int n = pow(2, exp);
        vector<int> arr;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, n - 1);

        for (int i = 0; i < n; ++i) {
            arr.push_back(dis(gen) % n);
        }

        auto start = high_resolution_clock::now();
        parallelInsertionSort(arr, 0, n - 1,max(100,512)); // Adjust the threshold value as needed
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "n = " << n << ": " << duration.count() / 1e6 << " seconds" << endl;
    }

    return 0;
}

