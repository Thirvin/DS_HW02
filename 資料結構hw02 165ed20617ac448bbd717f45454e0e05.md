# 資料結構hw02

## 目標

透過不同實驗比較insertion sort, merge sort, 三種randomized quick sort (Lomuto Partition, Hoare Parti

tion, 與3-Way Partition)與Counting sort。

## 實驗一

$$
產生一個大小為 n 的 array，其中 n = 2^{10}, 2^{11}, …, 2^{30}。
$$

$$
每個 arr[i] 為 0~n-1 隨機產生。
$$

$$
x 軸為 n 值：n = 2^{10}, 2^{11}, …, 2^{30}。
$$

$$
y 軸為每個演算法的執行時間（產生 10 個 input 後取平均）。
$$

### 程式碼

```cpp

// Insertion_sort.cpp

#include <cmath>
#include <ctime>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// 插入排序演算法的函數，對傳入的vector 進行排序
inline void F(vector<int>& arr) { 
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // 將大於 key 的元素向右移動
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // 將 key 放入正確的位置
        arr[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    // 從命令列參數中取得輸入大小 'n'
    int n = stoi(argv[1]);
    n = pow(2, n);
    vector<int> arr;

    // 生成大小為 '2^n' 的隨機array
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(gen) % n);
    }

    // 使用 'high_resolution_clock' 計時器測量插入排序的執行時間
    auto start = high_resolution_clock::now();
    F(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // 輸出執行時間（秒）
    cout << duration.count() / 1e6;
}
```

```cpp
//Merge_sort.cpp
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

// 函數 F: 執行合併排序演算法的遞迴部分
void F(vector<int>& arr, int l, int r) {
    if (r - l == 1) {
        return;
    }

    int mid = (l + r) / 2;

    F(arr, l, mid);
    F(arr, mid, r);

    int il = l;
    int ir = mid;
    int now = l;

    // 合併排序過程，將兩個已排序的子陣列合併成一個有序的陣列
    while (il < mid || ir < r) {
        if (ir >= r || (il < mid && arr[il] < arr[ir])) {
            temp[now++] = arr[il++];
        } else {
            temp[now++] = arr[ir++];
        }
    }

    // 複製合併後的結果回原陣列
    for (int i = l; i < r; i++) {
        arr[i] = temp[i];
    }
}

int main(int argc, char *argv[]) {
    // 從命令列參數中取得輸入大小 'n'
    int n = stoi(argv[1]);
    n = pow(2, n);
    vector<int> arr;
    temp.resize(n);

    // 生成大小為 '2^n' 的隨機array
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(gen) % n);
    }

    // 使用 'high_resolution_clock' 計時器測量合併排序的執行時間
    auto start = high_resolution_clock::now();
    F(arr, 0, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // 輸出執行時間（秒）
    cout << duration.count() / 1e6;
}
```

```cpp
// Quick_sort1.cpp
#include <cmath>
#include <ctime>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

vector<int> temp;

// 快速排序的partition，使用Lomuto Partition 
int Partition(vector<int>& arr, int l, int r) {
    // 隨機選擇一個元素作為pivot
    int x = l + rand() % (r - l);
    int pivot = arr[x];
    swap(arr[r - 1], arr[x]); // 將pivot與陣列最後一個元素交換位置 保證pivot最後會被放在i

    int i = l - 1;

    // 將小於pivot的元素移到陣列左側
    for (int j = l; j < r; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    return i; // 返回最後一格<=pivot的位置
}

// 遞迴執行Quick sort
void F(vector<int>& arr, int l, int r) {
    if (l < r) {
        int p = Partition(arr, l, r);
        F(arr, l, p);
        F(arr, p + 1, r);
    }
}

int main(int argc, char *argv[]) {
    srand(time(0));

    // 從命令列參數中取得輸入大小 'n'
    int n = stoi(argv[1]);
    n = pow(2, n);
    vector<int> arr;
    temp.resize(n);

    // 生成大小為 '2^n' 的隨機array
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(gen) % n);
    }
    // 使用 'high_resolution_clock' 計時器測量快速排序的執行時間
    auto start = high_resolution_clock::now();
    F(arr, 0, n);
    auto stop = high_resolution_clock::now();
    // 輸出執行時間（秒）
    auto duration = duration_cast<microseconds>(stop - start);
    cout  << duration.count() / 1e6;
}
```

```cpp
// Quick_sort2.cpp
#include <cmath>
#include <ctime>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

vector<int> temp;

// 快速排序的 Partition 函數，使用 Hoare Partition 
int Partition(vector<int>& arr, int l, int r) {
    // 隨機選擇一個元素作為 pivot
    int x = l + rand() % (r - l);
    int pivot = arr[x];
    int i = l;
    int j = r-1;

    while (1) {
        while (arr[i] < pivot ) i ++; //找到第一個>= pivot的數
        while (arr[j] > pivot ) j --; //找到第一個<= pivot的數
        if (i >= j)                   //兩個交錯 代表分好了
            return j;
        swap(arr[i], arr[j]); // 交換
    }
}

// 遞迴執行 Quick Sort
void F(vector<int>& arr, int l, int r) {
    if (l < r) {
        int p = Partition(arr, l, r);
        F(arr, l, p);
        F(arr, p + 1, r);
    }
}

int main(int argc, char *argv[]) {
    srand(time(0));

    // 從命令列參數中取得輸入大小 'n'
    int n = stoi(argv[1]);
    n = pow(2, n);
    vector<int> arr;
    temp.resize(n);

    // 生成大小為 '2^n' 的隨機 array
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(gen) % n);
    }

    // 使用 'high_resolution_clock' 計時器測量快速排序的執行時間
    auto start = high_resolution_clock::now();
    F(arr, 0, n);
    auto stop = high_resolution_clock::now();

    // 輸出執行時間（秒）
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1e6;
}
```

```cpp
// Quick_sort3.cpp
#include <cmath>
#include <ctime>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

vector<int> temp;

// 快速排序的 Partition 函數，使用三分割的 Hoare Partition Scheme
int* Partition(vector<int>& arr, int l, int r) {
    // 隨機選擇一個元素作為 pivot
    int x = l + rand() % (r - l);
    int pivot = arr[x];

    // 初始化三個指標，lt: 小於 pivot 的區域的結尾，gt: 大於 pivot 的區域的開始，i: 當前檢查的元素
    int lt = l;
    int gt = r - 1;
    int i = l;

    while (i <= gt) {
        if (arr[i] < pivot) {
            // 將當前元素與小於 pivot 的區域的結尾元素交換，並移動相應指標
            swap(arr[i], arr[lt]);
            ++i;
            ++lt;
        } else if (arr[i] > pivot) {
            // 將當前元素與大於 pivot 的區域的開始元素交換，並移動相應指標
            swap(arr[i], arr[gt]);
            --gt;
        } else {
            // 當前元素等於 pivot，只需移動檢查指標
            ++i;
        }
    }

    // 回傳包含小於 pivot 區域結尾和大於 pivot 區域開始的兩個指標
    int* indices = new int[2];
    indices[0] = lt;
    indices[1] = gt;

    return indices;
}

// 遞迴執行 Quick Sort
void F(vector<int>& arr, int l, int r) {
    if (l < r) {
        int* p = Partition(arr, l, r);
        F(arr, l, p[0]);
        F(arr, p[1] + 1, r);  
        delete[] p;
    }
}

int main(int argc, char *argv[]) {
    srand(time(0));

    // 從命令列參數中取得輸入大小 'n'
    int n = stoi(argv[1]);
    n = pow(2, n);
    vector<int> arr;
    temp.resize(n);

    // 生成大小為 '2^n' 的隨機 array
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(gen) % n);
    }

    // 使用 'high_resolution_clock' 計時器測量快速排序的執行時間
    auto start = high_resolution_clock::now();
    F(arr, 0, n);
    auto stop = high_resolution_clock::now();

    // 輸出執行時間（秒）
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1e6;
}
```

```cpp
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

int **Count;  // 用於記錄數字出現次數的陣列
int mi, mx;   // 最大值和最小值
int n;        // 輸入大小

// 計數排序的函數
inline void F() {
    mx = 0;
    mi = n;

    // 將每個數字出現的次數記錄在 Count[1] 中
    for (int i = 0; i < n; ++i) {
        Count[1][Count[0][i]] += 1;
        mx = max(mx, Count[0][i]);
        mi = min(mi, Count[0][i]);
    }

    // 將記錄的次數轉換為排序後的array
    int now = 0;
    for (int i = mi; i <= mx; i++) {
        while (Count[1][i]-- > 0) {
            Count[0][now++] = i;
        }
    }
}

int main(int argc, char *argv[]) {
    n = stoi(argv[1]);
    n = pow(2, n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);

    // 初始化記錄數組的陣列 Count
    Count = new int *[2];
    Count[0] = new int[n];
    Count[1] = new int[n];

    // 隨機生成大小為 '2^n' 的array
    for (int i = 0; i < n; ++i) {
        Count[1][i] = 0;
        Count[0][i] = (dis(gen) % n);
    }

    // 使用 'high_resolution_clock' 計時器測量計數排序的執行時間
    auto start = high_resolution_clock::now();
    F();
    auto stop = high_resolution_clock::now();

    // 輸出執行時間（秒）
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1e6;

    // 釋放動態分配的記憶體
    delete[] Count[0];
    delete[] Count[1];
    delete[] Count;

    return 0;
}
```

### 實驗結果

Quick_sort1是Lomuto

Quick_sort2是Hoare

Quick_sort3是3 way

![Untitled](%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8Bhw02%20165ed20617ac448bbd717f45454e0e05/Untitled.png)

### 結論

可以看到Insertion sort是最慢的，和其他sort不在同一個數量級，如果把insertoin sort拔掉，看看剩下的圖，

![Untitled](%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8Bhw02%20165ed20617ac448bbd717f45454e0e05/Untitled%201.png)

 可以看到在$2^{30}$的時候花的時間大小為：

Merge sort >  Quick sort 3 way partition > Counting sort > Quick sort Lomuto parition > Quick sort Hoare’s parition

Quick sort和 Merge sort的複雜度都是$O(N\times logN)$，可是可以發現Merge sort和Quick sort的時間差距隨著n變大而變大，猜測可能是Cache的關係，因為Merge sort在Merge的時候會用到額外的空間，當n很大的時候，很容易造成cache misses，所以常數會隨著n而變大，後來有試著尋找不會用到額外空間的in-place merge sort，但是，不是常數太大就是複雜度太大，所以比較下來還是需要extra space的merge sort速度更快。

觀察三個Quick sort，可以看到最快的是Hoare's partition，再來是Lomuto最慢的是3 way，比較一下三個partition，可以發現Hoare’s partition每次可以把兩個數字放到正確的位置，所以最多只要交換n/2次，而3 way partition或是 Lomuto都最多要n次，不過，Lomuto只有在小於pivot的時候才swap，而3 way partition只有在不等於pivot時swap，所以平均會比Lomuto交換的次數還多，所以時間比較久。

而Counting Sort花的時間在$2^{30}$以前Hoare's partition的Quick sort速度差不多，甚至比較快，可是在接近$2^{30}$的時候快速升高時間，猜測是因為用到的記憶體太大，所以Cache misses上升，導致整體的複雜度上升，所以讓$O(N)$的Counting Sort 比 $O(N\times logN)$的Quick sort慢。

## 實驗二

$$
 產生一個大小為2^20的排序好的array（換句話說，arr[i]=i）。 \\ 
隨機swap\space array內容k次，k=2^0,2^1,2^2,…,2^{20}。\\
  x軸為k值：k=2^0,2^1,2^2,…,2^{20}。  y軸為每個演算法的執行時間（產生10個input後取平均）。 
$$

## 程式碼

程式碼都和graph1差不多，只有生成array的方式有差

```cpp
for (int i = 0; i < n; ++i) {
		Count[i] = 0;
        arr.push_back(i);
    }
	while(k--){
		int a = gen() % n;
		int b = gen() % n;
		swap(arr[a],arr[b]);
	}
```

### 結論

![Untitled](%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8Bhw02%20165ed20617ac448bbd717f45454e0e05/Untitled%202.png)

可以發現在$k=2^{11}$之後，insertoin sort的時間大幅增加，我們看一下之前的圖。

![Untitled](%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8Bhw02%20165ed20617ac448bbd717f45454e0e05/Untitled%203.png)

可以看到在$2^7$之前insertion sort的速度都不慢，不過之後就快速上升，我的推論是，假設把$a_0$換到$a_n$，在insertion sort的時候會需要再swap n次才能把他換回去，而n最大為陣列長度，因為陣列長度為$2^{20}$是常數，所以複雜度只和交換次數有關，推論swap k次後的複雜度為，$O(k)$，，所以可以看到insertion sort所需的時間會隨著k上升而線性上升，符合推論。

而對於其他的sort來說，可以從圖看出，swap次數和時間無關：

對merge sort來說：不管swap幾次，都會花一樣的時間在，divide和merge上，

對quick sort來說：swap次數只會稍微影響partition中的swap次數，所以只會影響到一點常數，所以整體來說時間影響不大。

對counting sort來說：一樣要跑過array紀錄，然後把數字放回去，唯一的影響就只有，因為swap之後數字間隔變大，所以造成cache misses稍微增加，讓常數稍微改變，但是整體影響不大，所以swap次數不會有太大的影響。

## 實驗三

$$
 產生一個大小為2^20的array。  每個arr[i]為0~k-1隨機產生。  x軸為k值：k=2^0,2^1,2^2,…,2^{20}。  y軸為每個演算法的執行時間（產生10個input後取平均）。 
$$

## 程式碼

程式碼也都和之前差不多，arr改成要mod k。

```cpp
for (int i = 0; i < n; ++i) {
        arr.push_back(gen()%k);
}
```

### 結論

![Untitled](%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8Bhw02%20165ed20617ac448bbd717f45454e0e05/Untitled%204.png)

觀察整張圖可以發現Quick sort in Lomuto partition的線和insertion sort的線長的特別奇怪：

先從Lomuto看起，可以看到當k很小時，Lomuto的時間很大，甚至在我多分配1G記憶體後才沒有達到遞迴深度，因為Lomuto在遇到重複元素的時候會導致每次divide之後沒辦法有效率的縮小問題，可以想像，當一段區間範圍$[l,r)$的內容完全相同的時候，Lomuto解決這段區間的複雜度會是$O(n^2),n =r-l.$，所以當重複元素變多時，會導致整體複雜度上升，當陣列全部元素都相同時，複雜度最差會到$O(N^2),N\space is\ the \ size \ of \ array$，所以整體時間會隨著k上升而減少。

對insertion sort來說，裡面的元素重複越多，就愈接近排好的狀態，所以如同上一個實驗的結論，當元素重複的數量越多時，insertion sort的速度會越快，最快的複雜度為$O(N)$，而當重複個數減少時，又會回到最初的$O(N^2)$，所以整體時間也會隨著，k上升而上升。

把極端的insertoin sort和Lomuto拔掉之後，再次觀察數據。

![Untitled](%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8Bhw02%20165ed20617ac448bbd717f45454e0e05/Untitled%205.png)

可以看到，3 way partition的時間有明顯的浮動，因為3 way partition中會把array切成三個部分，< pivot，= pivot和>pivot，而我們會繼續遞迴的時候只會遞迴<pivot和>pivot的部分，所以3 way partition在重複元素很多的時候可以有效率地把問題變小，最快的複雜度只要$O(N)$，所以花費時間會隨著k上升而上升，最慢到$O(N\times \log N)$。

Merge sort、Counting sort和Hoare’s partition的花費時間都不太會隨k有大幅變化，也只有和實驗二差不多的常數變化。

## 總結

從實驗結果可以看出，不同的排序算法對不同的資料有不同的適應能力。在面對重複元素較多的情況下，Insertion sort表現較好；而使用Lomuto partition的Quick sort在處理重複元素較少的情況下表現很差。3 way partition的Quick sort在處理含有大量重複元素的數組時效率較高。Merge sort、Counting sort和Hoare's partition的Quick sort的時間消耗相對穩定，不會隨著數據特性的改變而有明顯的變化。然而，Merge sort和Counting sort需要的額外空間複雜度為$O(max(a_i)):$（陣列中最大的元素），因此當陣列長度和元素大小差不多時，Counting sort的表現會比Merge sort好；反之，Merge Sort表現較好。而Quick sort的表現則取決於pivot的選擇，但在大多數情況下都表現良好。

## 心得、疑問、與遇到的困難

這次的實驗和上次相比沒有那麼摧殘電腦，大部分的資料都有跑完，除了insertion sort graph1的資料，所以最後只能仰賴curve fitting的力量，這次curve fitting的方法是用ANN去fitting，畢竟號稱能fit所有function，所以就想嘗試看看，其實在驗證cache是quick sort比merge sort快的原因時，有想要找不用extrap space的merge sort來測試，不過發現，可以time complexity$O(N\times logN)$而且space complexity$O(1)$的merge方法時，發現in place merge sort的常數太大了，特別是當N很大的時候必須要開到long long，然而long long的mod運算又特別慢，所以導致整體時間比一般的merge sort還慢，所以沒有透過這方式得到很好的結論，或許能透過實驗驗證的方法只有一台cache可以塞下所有資料的電腦才能得出結論？

source code:[https://github.com/Thirvin/DS_HW02](https://github.com/Thirvin/DS_HW02)