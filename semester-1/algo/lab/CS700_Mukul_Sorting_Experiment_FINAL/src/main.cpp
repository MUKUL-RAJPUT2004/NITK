#include <bits/stdc++.h>
using namespace std;

/*
 CS-700 Sorting Experiment
 Purpose:
 1. Compare QuickSort pivot strategies.
 2. Compare QuickSort with other sorting algorithms.
*/

using SortFunction = function<void(vector<int>&)>;

long long comparisons = 0;

/* ---------- Bubble Sort ---------- */
void bubbleSort(vector<int>& a) {
    for (int i = 0; i + 1 < (int)a.size(); ++i) {
        bool swapped = false;
        for (int j = 0; j + 1 < (int)a.size() - i; ++j) {
            ++comparisons;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

/* ---------- Insertion Sort ---------- */
void insertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); ++i) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0) {
            ++comparisons;
            if (a[j] > key) {
                a[j + 1] = a[j];
                --j;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}

/* ---------- Merge Sort ---------- */
void mergeParts(vector<int>& a, int l, int m, int r) {
    vector<int> left(a.begin() + l, a.begin() + m + 1);
    vector<int> right(a.begin() + m + 1, a.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < (int)left.size() && j < (int)right.size()) {
        ++comparisons;
        if (left[i] <= right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }

    while (i < (int)left.size()) a[k++] = left[i++];
    while (j < (int)right.size()) a[k++] = right[j++];
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    mergeParts(a, l, m, r);
}

/* ---------- QuickSort ---------- */

int partitionFirst(vector<int>& a, int l, int r) {
    int pivot = a[l];
    int i = l + 1;

    for (int j = l + 1; j <= r; ++j) {
        ++comparisons;
        if (a[j] < pivot) swap(a[i++], a[j]);
    }

    swap(a[l], a[i - 1]);
    return i - 1;
}

int partitionRandom(vector<int>& a, int l, int r) {
    int p = l + rand() % (r - l + 1);
    swap(a[l], a[p]);
    return partitionFirst(a, l, r);
}

int medianOfThreeValue(int x, int y, int z) {
    if ((x <= y && y <= z) || (z <= y && y <= x)) return y;
    if ((y <= x && x <= z) || (z <= x && x <= y)) return x;
    return z;
}

int partitionMedian3(vector<int>& a, int l, int r) {
    int m = l + (r - l) / 2;
    int median = medianOfThreeValue(a[l], a[m], a[r]);

    if (a[m] == median) swap(a[l], a[m]);
    else if (a[r] == median) swap(a[l], a[r]);

    return partitionFirst(a, l, r);
}

template <typename PartitionFunction>
void quickSort(vector<int>& a, int l, int r, PartitionFunction partitionFunction) {
    /*
       Recurse on the smaller side first and process the larger side
       iteratively. This keeps recursion depth small for large inputs.
    */
    while (l < r) {
        int p = partitionFunction(a, l, r);

        if (p - l < r - p) {
            quickSort(a, l, p - 1, partitionFunction);
            l = p + 1;
        } else {
            quickSort(a, p + 1, r, partitionFunction);
            r = p - 1;
        }
    }
}

void quickFirst(vector<int>& a) {
    if (!a.empty()) quickSort(a, 0, (int)a.size() - 1, partitionFirst);
}

void quickRandom(vector<int>& a) {
    if (!a.empty()) quickSort(a, 0, (int)a.size() - 1, partitionRandom);
}

void quickMedian3(vector<int>& a) {
    if (!a.empty()) quickSort(a, 0, (int)a.size() - 1, partitionMedian3);
}

/* ---------- Heap Sort ---------- */
void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        ++comparisons;
        if (a[l] > a[largest]) largest = l;
    }

    if (r < n) {
        ++comparisons;
        if (a[r] > a[largest]) largest = r;
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    for (int i = (int)a.size() / 2 - 1; i >= 0; --i)
        heapify(a, (int)a.size(), i);

    for (int i = (int)a.size() - 1; i > 0; --i) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

/* ---------- Radix Sort ---------- */
void radixSort(vector<int>& a) {
    if (a.empty()) return;

    int maximum = *max_element(a.begin(), a.end());

    for (long long exp = 1; maximum / exp > 0; exp *= 10) {
        vector<int> output(a.size());
        int count[10] = {};

        for (int x : a) ++count[(x / exp) % 10];
        for (int i = 1; i < 10; ++i) count[i] += count[i - 1];

        for (int i = (int)a.size() - 1; i >= 0; --i) {
            int digit = (a[i] / exp) % 10;
            output[count[digit] - 1] = a[i];
            --count[digit];
        }

        a.swap(output);
    }
}

/* ---------- Utilities ---------- */
vector<int> readInput(const string& path) {
    ifstream file(path);
    if (!file) {
        cerr << "\nERROR: Cannot open input file:\n" << path << "\n";
        exit(1);
    }

    vector<int> data;
    int x;
    while (file >> x) data.push_back(x);
    return data;
}

double runAndTime(const string& algorithm, const vector<int>& original,
                  long long& comparisonCount) {
    vector<int> data = original;
    comparisons = 0;

    auto start = chrono::high_resolution_clock::now();

    if (algorithm == "Bubble Sort") bubbleSort(data);
    else if (algorithm == "Insertion Sort") insertionSort(data);
    else if (algorithm == "Merge Sort") mergeSort(data, 0, data.size() - 1);
    else if (algorithm == "Quick - First Pivot") quickFirst(data);
    else if (algorithm == "Quick - Random Pivot") quickRandom(data);
    else if (algorithm == "Quick - Median of Three") quickMedian3(data);
    else if (algorithm == "Heap Sort") heapSort(data);
    else if (algorithm == "Radix Sort") radixSort(data);

    auto finish = chrono::high_resolution_clock::now();

    if (!is_sorted(data.begin(), data.end())) {
        cerr << "ERROR: " << algorithm << " did not sort correctly.\n";
        exit(1);
    }

    comparisonCount = comparisons;

    return chrono::duration<double, milli>(finish - start).count();
}

/*
 Bubble and insertion are O(n^2). We stop them above 20,000
 because using 500,000 elements would make the experiment
 unnecessarily long.
*/
bool isQuadratic(const string& algorithm) {
    return algorithm == "Bubble Sort" || algorithm == "Insertion Sort";
}

const vector<int> SIZES = {10000, 25000, 50000, 100000, 200000, 500000};
const vector<string> TYPES = {"random", "ascending", "descending"};
const int QUADRATIC_LIMIT = 20000;
const int DEFAULT_ROUNDS = 5;

string typeFolder(const string& type) {
    if (type == "ascending") return "ascending";
    if (type == "descending") return "descending";
    return "random";
}

void performOne(const string& algorithm, const string& type, int n,
                int rounds, ofstream& output) {
    string path = "datasets/" + typeFolder(type) +
                  "/input_" + to_string(n) + ".txt";

    vector<int> input = readInput(path);

    for (int round = 1; round <= rounds; ++round) {
        long long count = 0;
        double timeMs = runAndTime(algorithm, input, count);

        output << algorithm << ","
               << type << ","
               << n << ","
               << round << ","
               << fixed << setprecision(6)
               << timeMs << ","
               << count << "\n";

        output.flush();
    }
}

void runExperiment(const vector<string>& algorithms, int rounds,
                   ofstream& output) {
    for (const string& type : TYPES) {
        for (int n : SIZES) {
            cout << "\n--- " << type << " input | n = " << n << " ---\n";

            for (const string& algorithm : algorithms) {
                if (isQuadratic(algorithm) && n > QUADRATIC_LIMIT) {
                    cout << "[SKIP] " << algorithm
                         << " : O(n^2), n > " << QUADRATIC_LIMIT << "\n";
                    continue;
                }

                cout << "[RUN ] " << algorithm
                     << " | " << rounds << " rounds\n";

                performOne(algorithm, type, n, rounds, output);

                cout << "[DONE] " << algorithm << "\n";
            }
        }
    }
}

void printMenu() {
    cout << "\n";
    cout << "====================================================\n";
    cout << "             CS-700 SORTING EXPERIMENT\n";
    cout << "====================================================\n";
    cout << "  QUICK SORT STUDY\n";
    cout << "   [1] First Pivot\n";
    cout << "   [2] Random Pivot\n";
    cout << "   [3] Median-of-Three Pivot\n";
    cout << "\n";
    cout << "  ALGORITHM COMPARISON\n";
    cout << "   [4] Run all sorting algorithms\n";
    cout << "   [5] Run complete experiment\n";
    cout << "\n";
    cout << "   [0] Exit\n";
    cout << "====================================================\n";
}

int main() {
    srand((unsigned)time(nullptr));

    filesystem::create_directories("results");

    ofstream output("results/results.csv");
    if (!output) {
        cerr << "ERROR: Could not create results/results.csv\n";
        cerr << "Run the program from the project ROOT folder.\n";
        return 1;
    }

    output << "algorithm,input_type,input_size,round,time_ms,comparisons\n";

    const vector<string> quickAlgorithms = {
        "Quick - First Pivot",
        "Quick - Random Pivot",
        "Quick - Median of Three"
    };

    const vector<string> allAlgorithms = {
        "Bubble Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick - First Pivot",
        "Quick - Random Pivot",
        "Quick - Median of Three",
        "Heap Sort",
        "Radix Sort"
    };

    while (true) {
        printMenu();

        cout << "Select an operation [0-5]: ";
        int choice;
        cin >> choice;

        if (!cin) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            cout << "\nExperiment program closed.\n";
            break;
        }

        if (choice >= 1 && choice <= 3) {
            int rounds;
            cout << "\nNumber of rounds [" << DEFAULT_ROUNDS << "]: ";
            cin >> rounds;

            if (rounds < 1) {
                cout << "Rounds must be at least 1.\n";
                continue;
            }

            runExperiment({quickAlgorithms[choice - 1]}, rounds, output);
            cout << "\nQuickSort experiment completed.\n";
            cout << "Results saved in results/results.csv\n";
        }

        else if (choice == 4) {
            int rounds;
            cout << "\nNumber of rounds [" << DEFAULT_ROUNDS << "]: ";
            cin >> rounds;

            if (rounds < 1) {
                cout << "Rounds must be at least 1.\n";
                continue;
            }

            runExperiment(allAlgorithms, rounds, output);
            cout << "\nAlgorithm comparison completed.\n";
            cout << "Results saved in results/results.csv\n";
        }

        else if (choice == 5) {
            int rounds;
            cout << "\nInput files are already prepared in datasets/.\n";
            cout << "Sizes: 10K, 25K, 50K, 100K, 200K, 500K\n";
            cout << "Types: random, ascending, descending\n";
            cout << "Number of rounds [" << DEFAULT_ROUNDS << "]: ";
            cin >> rounds;

            if (rounds < 1) {
                cout << "Rounds must be at least 1.\n";
                continue;
            }

            cout << "\nStarting complete experiment...\n";
            runExperiment(allAlgorithms, rounds, output);

            cout << "\n====================================================\n";
            cout << " COMPLETE EXPERIMENT FINISHED\n";
            cout << " Results: results/results.csv\n";
            cout << "====================================================\n";
        }

        else {
            cout << "Invalid choice. Select 0-5.\n";
        }
    }

    output.close();
    return 0;
}
