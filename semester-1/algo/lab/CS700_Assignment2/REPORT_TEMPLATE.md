# CS-700 Assignment 2 — Experimental Analysis

## 1. Objective
Compare three QuickSort pivot strategies and then compare the selected
QuickSort with Bubble, Insertion, Merge, Heap and Radix Sort.

## 2. Input Data
The same fixed datasets are used for every algorithm:
- Random
- Sorted
- Reverse sorted

Input sizes:
10,000; 20,000; 50,000; 100,000; 200,000.

## 3. Repetitions
Each experiment is repeated 5 times. Average execution time is used.

## 4. Experiment 1
Compare:
- First pivot
- Random pivot
- Median-of-three pivot

Insert:
- quick_random_time.png
- quick_sorted_time.png
- quick_reverse_time.png

Discuss the best pivot strategy.

## 5. Experiment 2
Compare:
- Bubble
- Insertion
- Merge
- QuickSort
- Heap
- Radix

Insert:
- all_random_time.png
- all_sorted_time.png
- all_reverse_time.png

## 6. Comparisons
Insert comparisons_vs_time.png.

## 7. Observations
Write observations from your actual CSV/graphs. Do not invent values.

## 8. Conclusion
State which QuickSort pivot strategy performed best and how the
sorting algorithms differed experimentally.
