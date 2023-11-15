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
void F(vector<int>& arr,int l,int r) {
	if(r - l == 1){
		return ;
	}

	int mid = (l+r) / 2;

	F(arr,l,mid);
	F(arr,mid,r);
	int il = l;
	int ir = mid;
	int now = l;
	while(il < mid or ir < r){
		if(ir >= r or(il < mid and arr[il] < arr[ir])){
			temp[now++] = arr[il++];
		}else{
			temp[now++] = arr[ir++];
		}
	}
	for(int i = l;i < r;i ++){
		arr[i] = temp[i];
	}
}

int main(int argc,char *argv[]){
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
