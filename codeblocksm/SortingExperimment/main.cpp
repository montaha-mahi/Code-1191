#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// ------------- Bubble Sort -------------
void bubbleSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ------------- Merge Sort -------------
void merge(vector<int> &a, int l, int m, int r) {
    vector<int> left(a.begin() + l, a.begin() + m + 1);
    vector<int> right(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }
    while (i < (int)left.size()) a[k++] = left[i++];
    while (j < (int)right.size()) a[k++] = right[j++];
}

void mergeSortRec(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortRec(a, l, m);
    mergeSortRec(a, m + 1, r);
    merge(a, l, m, r);
}

void mergeSort(vector<int> &a) {
    if (a.size() > 1) mergeSortRec(a, 0, a.size() - 1);
}

// ------------- Quick Sort -------------
int partition(vector<int> &a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSortRec(vector<int> &a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSortRec(a, low, pi - 1);
        quickSortRec(a, pi + 1, high);
    }
}

void quickSort(vector<int> &a) {
    if (a.size() > 1) quickSortRec(a, 0, a.size() - 1);
}

// ------------- I/O and timing -------------
vector<int> readFile(const string &filename, int n) {
    vector<int> a(n);
    ifstream fin(filename);
    for (int i = 0; i < n; i++) fin >> a[i];
    fin.close();
    return a;
}

template <typename Func>
double measureAvgTime(Func sortFunc, const vector<int> &data, int runs) {
    double total = 0;
    for (int r = 0; r < runs; r++) {
        vector<int> v = data; // untimed copy
        auto start = high_resolution_clock::now();
        sortFunc(v);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total += duration.count();
    }
    return total / runs;
}

int main() {
    vector<int> sizes = {100, 1000, 10000, 50000, 100000};
    const int RUNS = 5;

    cout << left << setw(12) << "Input Size"
         << setw(18) << "Bubble Sort(us)"
         << setw(18) << "Merge Sort(us)"
         << setw(18) << "Quick Sort(us)" << "\n";
    cout << string(66, '-') << "\n";

    ofstream results("results.csv");
    results << "InputSize,BubbleSort,MergeSort,QuickSort\n";

    for (int n : sizes) {
        string filename = "input" + to_string(n) + ".txt";
        vector<int> data = readFile(filename, n);

        double bubbleTime = measureAvgTime([](vector<int> &v){ bubbleSort(v); }, data, RUNS);
        double mergeTime  = measureAvgTime([](vector<int> &v){ mergeSort(v); }, data, RUNS);
        double quickTime  = measureAvgTime([](vector<int> &v){ quickSort(v); }, data, RUNS);

        cout << left << setw(12) << n
             << setw(18) << fixed << setprecision(2) << bubbleTime
             << setw(18) << fixed << setprecision(2) << mergeTime
             << setw(18) << fixed << setprecision(2) << quickTime << "\n";

        results << n << "," << bubbleTime << "," << mergeTime << "," << quickTime << "\n";
    }

    results.close();
    cout << "\nResults saved to results.csv\n";
    return 0;
}
