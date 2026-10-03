# CS-700 SORTING EXPERIMENT — VIVA CHEAT SHEET

## A. WHAT IS THIS ASSIGNMENT TRYING TO FIND?

There are TWO main questions:

### Experiment 1 — Which QuickSort pivot strategy behaves better?

We compare:

1. First element as pivot
2. Random element as pivot
3. Median-of-three pivot

We test them on:
- random input
- ascending input
- descending input

### Experiment 2 — How does QuickSort compare with other sorting algorithms?

We compare:
- Bubble Sort
- Insertion Sort
- Merge Sort
- QuickSort
- Heap Sort
- Radix Sort

The program records execution time and comparison count.

---

# B. INPUTS

Input files are ALREADY PROVIDED.

There are three input types:

### random
Elements are randomly shuffled.

### ascending
1 2 3 4 5 ... n

### descending
n n-1 n-2 ... 2 1

Why three types?

Because sorting algorithms can behave differently depending on
the initial arrangement of the data.

Sizes:

10,000
25,000
50,000
100,000
200,000
500,000

Why increasing sizes?

To observe how running time changes as n grows.

---

# C. NUMBER OF ROUNDS

Default:

5 rounds per experiment.

For example:

QuickSort + random + n=100000 + 5 rounds

means:

Run 1
Run 2
Run 3
Run 4
Run 5

The CSV stores every run.

Why repeat?

Execution time can fluctuate because of:
- operating-system scheduling
- background processes
- CPU state
- memory/cache effects

So repeated runs give a more reliable average.

The graph script uses the MEAN of the repeated runs.

---

# D. WHY DOES THE CONSOLE SAY [RUN]?

Example:

[RUN ] Quick - Random Pivot | 5 rounds

It means:

"The program is now executing this algorithm five times
on the current input."

Then:

[DONE] Quick - Random Pivot

means all requested repetitions for that combination finished.

---

# E. WHY DOES IT SAY [SKIP]?

Example:

[SKIP] Bubble Sort : O(n^2), n > 20000

This is intentional.

Bubble Sort and Insertion Sort are O(n^2).

For n = 500000:

n^2 = 250,000,000,000

That is an enormous number of operations.

Running them at every large size would make the experiment
unnecessarily long.

Therefore this implementation measures them only up to 20,000.

IMPORTANT VIVA ANSWER:

"We skip quadratic algorithms at very large input sizes because
their O(n^2) growth makes the experiment computationally impractical.
The faster algorithms are still tested up to 500,000."

---

# F. WHY 500,000?

500,000 is large enough to make differences between efficient
algorithms visible while still being practical for the machine.

It is a benchmark size, not a theoretical requirement unless
your assignment sheet explicitly specifies it.

---

# G. WHY ARE INPUTS SAVED BEFOREHAND?

The datasets are stored in:

datasets/

Why?

Every algorithm should receive the SAME data for a fair comparison.

If every algorithm generated its own random input, they would not
necessarily be tested on exactly the same values.

Pre-generated files make the experiment reproducible.

---

# H. WHY DOES THE PROGRAM COPY THE INPUT?

Inside runAndTime():

vector<int> data = original;

This is important.

The first sorting algorithm changes the array.

If we reused the already-sorted array for the next algorithm,
the experiment would be unfair.

Therefore each run starts with a fresh copy of the original input.

---

# I. WHAT EXACTLY IS BEING TIMED?

The program records:

time_ms

It starts the high-resolution clock immediately before the sorting
algorithm and stops it immediately after sorting.

The timing therefore measures the sorting operation rather than
file loading.

---

# J. WHY CHECK is_sorted()?

After every run:

is_sorted(data.begin(), data.end())

checks whether the algorithm actually produced sorted output.

If an implementation is wrong, the program stops instead of
silently producing invalid experimental data.

VIVA ANSWER:

"I included a correctness check so that timing results are only
accepted when the sorting algorithm actually sorts the input."

---

# K. QUICK SORT — FIRST PIVOT

The first element is chosen:

pivot = a[l]

Then the remaining elements are partitioned around it.

Potential problem:

If the input is already sorted and the first element is always
selected, the partitions can become highly unbalanced.

That leads toward:

T(n) = T(n-1) + O(n)

which gives:

O(n^2)

---

# L. QUICK SORT — RANDOM PIVOT

A random position is selected as pivot.

Why?

It reduces the chance of repeatedly getting a very bad pivot.

Expected complexity:

O(n log n)

Worst case:

O(n^2)

---

# M. QUICK SORT — MEDIAN OF THREE

Three values are considered:

first
middle
last

The median of these three is used as pivot.

Why?

It tries to choose a more representative pivot and reduce badly
unbalanced partitions.

It is a heuristic, NOT a guarantee of O(n log n).

Worst case remains O(n^2).

---

# N. WHY DO WE COMPARE FIRST/RANDOM/MEDIAN-OF-THREE?

Because theoretical complexity alone does not tell us everything
about practical performance.

We want to see:

- time
- comparison count
- effect of input order
- effect of pivot strategy

---

# O. OTHER ALGORITHMS

Bubble Sort:
Best: O(n) with early-stop implementation
Average: O(n^2)
Worst: O(n^2)

Insertion Sort:
Best: O(n)
Average: O(n^2)
Worst: O(n^2)

Merge Sort:
Best/Average/Worst: O(n log n)

Heap Sort:
Best/Average/Worst: O(n log n)

QuickSort:
Average/Expected: O(n log n)
Worst: O(n^2)

Radix Sort:
For fixed-width integers, commonly expressed as O(d(n+k)),
where d is number of digits and k is radix/base.

---

# P. WHY IS RADIX DIFFERENT?

Radix Sort is not comparison-based.

It processes digits.

Therefore its complexity is not described using the same
comparison-based recurrence as Merge Sort or QuickSort.

---

# Q. WHAT IS IN results.csv?

Columns:

algorithm
input_type
input_size
round
time_ms
comparisons

Example:

Quick - Random Pivot,
random,
100000,
3,
...

means:

QuickSort using random pivot
on random input
with n = 100000
third repetition.

---

# R. WHAT DOES "AVERAGE TIME" MEAN?

If five runs produce:

10 ms
12 ms
11 ms
9 ms
8 ms

average:

(10 + 12 + 11 + 9 + 8) / 5
= 10 ms

The Python graph program performs this averaging automatically.

---

# S. WHY DO WE HAVE A SEPARATE PYTHON SCRIPT?

C++:
- performs sorting
- measures time
- saves raw data

Python:
- reads the CSV
- calculates averages
- generates graphs

This separates experimentation from visualization.

---

# T. OUTPUT GRAPHS

After:

python plot_results.py

you get:

graphs/

quick_random.png
quick_ascending.png
quick_descending.png

These answer Experiment 1.

You also get:

overall_random.png
overall_ascending.png
overall_descending.png

These answer Experiment 2.

And:

comparisons_random.png

which helps analyze comparison counts.

---

# U. IMPORTANT VIVA QUESTIONS

Q: Why use the same input for different algorithms?

A: To make the comparison fair and reproducible.

Q: Why repeat each experiment?

A: Execution time fluctuates, so repeated runs and averaging
give a more reliable measurement.

Q: Why random pivot?

A: To reduce the likelihood of consistently bad partitions.

Q: Why median-of-three?

A: It uses three representative positions and attempts to choose
a better pivot.

Q: Can median-of-three guarantee O(n log n)?

A: No. Worst case is still O(n^2).

Q: Why can first-pivot QuickSort become O(n^2)?

A: If the pivot repeatedly produces partitions of sizes 0 and n-1.

Q: Why skip Bubble Sort for 500K?

A: Its O(n^2) growth makes such an experiment impractical.

Q: Why copy the input before every run?

A: Sorting modifies the array. Every run must start with the same
original data.

Q: Why check is_sorted()?

A: To verify correctness before accepting timing data.

Q: Does measured time equal theoretical complexity?

A: No. Complexity describes growth asymptotically; measured time
also depends on hardware, implementation, compiler, cache,
memory and system load.

Q: Why use -O2?

A: It enables compiler optimizations so the benchmark represents
optimized compiled C++ rather than an unoptimized build.

---

# V. ONE IMPORTANT WARNING

Do NOT claim that the experiment proves a universal winner.

Say:

"The experiment shows the observed performance on our chosen
machine, implementations and datasets."

That is scientifically correct.

---

# W. PROJECT STRUCTURE

src/main.cpp
    All sorting algorithms and benchmark logic.

datasets/
    Pre-generated input files.

results/results.csv
    Raw experimental measurements.

plot_results.py
    Reads CSV and creates graphs.

graphs/
    Generated figures.

---

# X. RUN COMMANDS

From the PROJECT ROOT:

g++ -std=c++17 -O2 src/main.cpp -o sorting.exe

Then:

.\sorting.exe

For a full experiment:

Choose [5]

Enter:

5

After completion:

results/results.csv

Then:

python plot_results.py

Graphs appear in:

graphs/

---

# Y. BEFORE VIVA — REMEMBER THIS ONE-LINER

"Same fixed datasets → multiple runs → measure sorting time →
verify sorted output → save raw results → average them → plot →
compare theory with experiment."
