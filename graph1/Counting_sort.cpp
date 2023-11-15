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
int **Count;
int mi,mx;
int n;
vector<int>arr;
inline void F() {
	mx = 0;
	mi = n;
    for (int i = 0; i < n; ++i) {
		Count[1][Count[0][i]] += 1;
		mx = max(mx,Count[0][i]);
		mi = min(mi,Count[0][i]);
    }
	cout<<mx<<" "<<mi<<" ";
	int now = 0;
	for(int i = mi;i <= mx;i ++){
		while(Count[1][i]-- > 0){
			Count[0][now++] = i;
		}
	}
}

int main(int argc,char *argv[]){
	n = stoi(argv[1]);
	n = pow(2,n);
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
	Count = new int*[2];
	Count[0] = new int[n];
	Count[1] = new int[n];
    for (int i = 0; i < n; ++i) {
		Count[1][i] = 0;
        Count[0][i] = (dis(gen) % n);
    }
	auto start = high_resolution_clock::now();
	F();		
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	
	cout<<duration.count() /1e6;
}
