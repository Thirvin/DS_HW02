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
int c = 0;
int Partition(vector<int>& arr, int l, int r){
	int x = l + rand() % (r - l);
	int pivot =arr[x];
//	swap(arr[x],arr[l]);
	int i = l-1;
	int j = r;
	while(1){
		while(arr[++i] < pivot);
		while(arr[--j] > pivot) ;
//		cout<<i<<" "<<j << "\n";
		if(i >= j)
			return j;
		swap(arr[i],arr[j]);
	}
}

void F(vector<int>& arr,int l,int r) {
	c ++;
	if (r - l > 1) {
		int p = Partition(arr, l, r);
		F(arr, l, p+1);
		F(arr, p + 1, r);
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
        arr.push_back(gen()%k);
    }
		
	auto start = high_resolution_clock::now();
	F(arr,0,n);	
//	for(int i: arr){
//		cout<<i<<" ";
//	}
   auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	cout<<duration.count() /1e6;
}
