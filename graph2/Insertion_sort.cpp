#include<cmath>
#include<ctime>
#include<cstring>
#include<vector>
#include<iostream>
#include <algorithm>
#include <chrono>
#include <random>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
using namespace chrono;

inline void F(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main(int argc,char *argv[]){
	int k = stoi(argv[1]);
	k = pow(2,k);
	int n = pow(2,20);
	vector<int> arr;
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(i);
    }
	while(k --){
		int a,b;
		a = gen()% n;
		b = gen()% n;
		swap(arr[a],arr[b]);
	}
	auto start = high_resolution_clock::now();
	F(arr);		
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	cout<<duration.count() /1e6;
}
