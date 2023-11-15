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
int a,b;
void Partition(vector<int>& arr, int l, int r) {
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
	a = lt;
	b = gt;
}

void F(vector<int>& arr, int l, int r) {
    if (l < r) {
        Partition(arr, l, r);
        F(arr, l, a);
        F(arr, b + 1, r); 
    }
}
int main(int argc,char *argv[]){
	srand(time(0));
	int n = stoi(argv[1]);
	n = pow(2,n);
	vector<int> arr;
	temp.resize(n);
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(gen) % n);
    }

	auto start = high_resolution_clock::now();
	F(arr,0,n);
   auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	cout<<duration.count() /1e6;
}
