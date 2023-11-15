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
int *Count;
int mi,mx;
int k;
vector<int>arr;
inline void F() {
    int n = arr.size();
	mx = 0;
	mi = n;
    for (int i = 0; i < n; ++i) {
		Count[arr[i]] += 1;
		mx = max(mx,arr[i]);
		mi = min(mi,arr[i]);
    }
	int now = 0;
	for(int i = mi;i <= mx;i ++){
		while(Count[i]-- > 0){
			arr[now++] = i;
		}
	}
}

int main(int argc,char *argv[]){
	k = stoi(argv[1]);
	k = pow(2,k);
	int n = pow(2,20);
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
	Count = new int[k];
	for(int i = 0;i < k;i ++){
		Count[i] = 0;
	}
    for (int i = 0; i < n; ++i) {
        arr.push_back(gen() % k);
    }
	auto start = high_resolution_clock::now();
	F();		
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	cout<<duration.count() /1e6;
}
