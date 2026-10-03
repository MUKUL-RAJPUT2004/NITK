#include <bits/stdc++.h>
#include <filesystem>
using namespace std;

long long comparisons = 0;

/* ---------------- QuickSort ---------------- */

int partitionFirst(vector<int>& a, int low, int high) {
    int pivot = a[low];
    int i = low + 1;

    for (int j = low + 1; j <= high; j++) {
        comparisons++;

        if (a[j] < pivot) {
            swap(a[i], a[j]);
            i++;
        }
    }

    swap(a[low], a[i - 1]);
    return i - 1;
}

int partitionRandom(vector<int>& a, int low, int high) {
    int p = low + rand() % (high - low + 1);
    swap(a[low], a[p]);

    return partitionFirst(a, low, high);
}

int medianOfThree(int x, int y, int z) {
    if ((x <= y && y <= z) || (z <= y && y <= x))
        return y;

    if ((y <= x && x <= z) || (z <= x && x <= y))
        return x;

    return z;
}

int partitionMedian3(vector<int>& a, int low, int high) {
    int mid = low + (high - low) / 2;

    int median = medianOfThree(a[low], a[mid], a[high]);

    if (a[mid] == median)
        swap(a[low], a[mid]);
    else if (a[high] == median)
        swap(a[low], a[high]);

    return partitionFirst(a, low, high);
}

void quickFirst(vector<int>& a, int low, int high) {
    if (low >= high)
        return;

    int p = partitionFirst(a, low, high);

    quickFirst(a, low, p - 1);
    quickFirst(a, p + 1, high);
}

void quickRandom(vector<int>& a, int low, int high) {
    if (low >= high)
        return;

    int p = partitionRandom(a, low, high);

    quickRandom(a, low, p - 1);
    quickRandom(a, p + 1, high);
}

void quickMedian3(vector<int>& a, int low, int high) {
    if (low >= high)
        return;

    int p = partitionMedian3(a, low, high);

    quickMedian3(a, low, p - 1);
    quickMedian3(a, p + 1, high);
}

/* ---------------- Bubble Sort ---------------- */

void bubbleSort(vector<int>& a) {
    int n = a.size();

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;

        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;

            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                changed = true;
            }
        }

        if (!changed)
            break;
    }
}

/* ---------------- Insertion Sort ---------------- */

void insertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;

            if (a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } else {
                break;
            }
        }

        a[j + 1] = key;
    }
}

/* ---------------- Merge Sort ---------------- */

void mergeParts(vector<int>& a, int low, int mid, int high) {
    vector<int> left(a.begin() + low, a.begin() + mid + 1);
    vector<int> right(a.begin() + mid + 1, a.begin() + high + 1);

    int i = 0, j = 0, k = low;

    while (i < (int)left.size() && j < (int)right.size()) {
        comparisons++;

        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    while (i < (int)left.size())
        a[k++] = left[i++];

    while (j < (int)right.size())
        a[k++] = right[j++];
}

void mergeSort(vector<int>& a, int low, int high) {
    if (low >= high)
        return;

    int mid = low + (high - low) / 2;

    mergeSort(a, low, mid);
    mergeSort(a, mid + 1, high);

    mergeParts(a, low, mid, high);
}

/* ---------------- Heap Sort ---------------- */

void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++;

        if (a[left] > a[largest])
            largest = left;
    }

    if (right < n) {
        comparisons++;

        if (a[right] > a[largest])
            largest = right;
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

/* ---------------- Radix Sort ---------------- */

void radixSort(vector<int>& a) {
    if (a.empty())
        return;

    int maximum = *max_element(a.begin(), a.end());

    for (long long exp = 1; maximum / exp > 0; exp *= 10) {
        vector<int> output(a.size());
        int count[10] = {};

        for (int x : a)
            count[(x / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = (int)a.size() - 1; i >= 0; i--) {
            int digit = (a[i] / exp) % 10;
            output[count[digit] - 1] = a[i];
            count[digit]--;
        }

        a = output;
    }
}

/* ---------------- Utilities ---------------- */

vector<int> readInput(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Unable to open input file: " + filename);
    }

    vector<int> data;
    int x;

    while (file >> x)
        data.push_back(x);

    return data;
}

bool isSorted(const vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i - 1] > a[i])
            return false;
    }

    return true;
}

double runAlgorithm(
    const string& algorithm,
    const vector<int>& original,
    long long& count
) {
    vector<int> a = original;
    comparisons = 0;

    auto start = chrono::high_resolution_clock::now();

    if (algorithm == "Quick_First")
        quickFirst(a, 0, a.size() - 1);
    else if (algorithm == "Quick_Random")
        quickRandom(a, 0, a.size() - 1);
    else if (algorithm == "Quick_Median3")
        quickMedian3(a, 0, a.size() - 1);
    else if (algorithm == "Bubble")
        bubbleSort(a);
    else if (algorithm == "Insertion")
        insertionSort(a);
    else if (algorithm == "Merge")
        mergeSort(a, 0, a.size() - 1);
    else if (algorithm == "Heap")
        heapSort(a);
    else if (algorithm == "Radix")
        radixSort(a);

    auto end = chrono::high_resolution_clock::now();

    if (!isSorted(a)) {
        cerr << "Sorting error in " << algorithm << endl;
        exit(1);
    }

    count = comparisons;

    return chrono::duration<double, milli>(end - start).count();
}

int main() try {
    srand((unsigned)time(nullptr));

    // Fixed datasets already stored in input/.
    vector<string> types = {"random", "sorted", "reverse"};
    vector<int> sizes = {10000, 20000, 50000, 100000, 200000};

    // Stage 1: compare QuickSort pivot choices on all large inputs.
    vector<string> quickAlgorithms = {
        "Quick_First",
        "Quick_Random",
        "Quick_Median3"
    };

    // Stage 2: quadratic algorithms are limited to 20,000.
    // Faster algorithms are tested up to 200,000.
    vector<string> allAlgorithms = {
        "Bubble",
        "Insertion",
        "Merge",
        "Quick_Median3",
        "Heap",
        "Radix"
    };

    const int QUICK_REPETITIONS = 5;
    const int FAST_REPETITIONS = 5;
    const int QUADRATIC_MAX_N = 20000;

    filesystem::create_directories("results");
    ofstream out("results/results.csv");
    if (!out) {
        cerr << "Unable to create results/results.csv. "
             << "Run the program from the project root and check folder permissions."
             << endl;
        return 1;
    }

    out << "stage,algorithm,type,n,run,time_ms,comparisons\n";

    cout << "Stage 1: QuickSort pivot experiment..." << endl;

    for (string type : types) {
        for (int n : sizes) {
            string filename =
                "input/" + type + "/n" + to_string(n) + ".txt";

            vector<int> input = readInput(filename);

            for (string algorithm : quickAlgorithms) {
                for (int run = 1; run <= QUICK_REPETITIONS; run++) {
                    long long count;

                    double time = runAlgorithm(
                        algorithm, input, count
                    );

                    out << "QuickPivot,"
                         << algorithm << ","
                         << type << ","
                         << n << ","
                         << run << ","
                         << fixed << setprecision(6)
                         << time << ","
                         << count << "\n";
                }
            }
        }
    }

    cout << "Stage 2: All sorting algorithms..." << endl;

    for (string type : types) {
        for (int n : sizes) {

            // Do not run O(n^2) algorithms on huge inputs.
            if (n > QUADRATIC_MAX_N) {
                vector<string> fastOnly = {
                    "Merge",
                    "Quick_Median3",
                    "Heap",
                    "Radix"
                };

                string filename =
                    "input/" + type + "/n" + to_string(n) + ".txt";

                vector<int> input = readInput(filename);

                for (string algorithm : fastOnly) {
                    for (int run = 1; run <= FAST_REPETITIONS; run++) {
                        long long count;

                        double time = runAlgorithm(
                            algorithm, input, count
                        );

                        out << "AllAlgorithms,"
                             << algorithm << ","
                             << type << ","
                             << n << ","
                             << run << ","
                             << fixed << setprecision(6)
                             << time << ","
                             << count << "\n";
                    }
                }
            }
            else {
                string filename =
                    "input/" + type + "/n" + to_string(n) + ".txt";

                vector<int> input = readInput(filename);

                for (string algorithm : allAlgorithms) {
                    for (int run = 1; run <= FAST_REPETITIONS; run++) {
                        long long count;

                        double time = runAlgorithm(
                            algorithm, input, count
                        );

                        out << "AllAlgorithms,"
                             << algorithm << ","
                             << type << ","
                             << n << ","
                             << run << ","
                             << fixed << setprecision(6)
                             << time << ","
                             << count << "\n";
                    }
                }
            }
        }
    }

    out.close();

    cout << endl;
    cout << "EXPERIMENT COMPLETE!" << endl;
    cout << "Results: results/results.csv" << endl;

    return 0;
}
catch (const exception& error) {
    cerr << error.what() << endl;
    return 1;
}
