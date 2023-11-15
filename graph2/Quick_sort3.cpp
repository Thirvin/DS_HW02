#include<cmath>
#include<ctime>
#include<cstring>
#include<vector>
#include<iostream>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;
vector<int> temp;
int* Partition(vector<int>& arr, int l, int r) {
    int x = l + rand() % (r - l);
    int pivot = arr[x];
    int lt = l;
	int gt = r - 1; 
    int i = l;

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[lt]);
            ++i;
            ++lt;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            --gt;
        } else {
            ++i;
        }
    }

    int* indices = new int[2];
    indices[0] = lt;
    indices[1] = gt;

    return indices;
}

void F(vector<int>& arr, int l, int r) {
    if (l < r) {
        int* p = Partition(arr, l, r);
        F(arr, l, p[0]);
        F(arr, p[1] + 1, r);  // "+1" to skip the equal elements region
        delete[] p;
    }
}
int main(int argc,char *argv[]){
	srand(time(0));
	int k = stoi(argv[1]);
	k = pow(2,k);
	int n = pow(2,20);
	vector<int> arr;
	temp.resize(n);
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(i);
    }
	while(k--){
		int a = gen() % n;
		int b = gen() % n;
		swap(arr[a],arr[b]);
	}
	auto start = high_resolution_clock::now();
	F(arr,0,n);	
   auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	cout<<duration.count() /1e6;
}
