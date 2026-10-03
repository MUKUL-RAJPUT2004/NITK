import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs("graphs", exist_ok=True)

data = pd.read_csv("results/results.csv")

# Average the 5 repetitions.
avg = data.groupby(
    ["stage", "algorithm", "type", "n"],
    as_index=False
).agg(
    time_ms=("time_ms", "mean"),
    comparisons=("comparisons", "mean")
)

# ---------- Stage 1 ----------
quick = avg[avg["stage"] == "QuickPivot"]

quick_names = [
    "Quick_First",
    "Quick_Random",
    "Quick_Median3"
]

for data_type in ["random", "sorted", "reverse"]:
    temp = quick[quick["type"] == data_type]

    plt.figure()

    for algorithm in quick_names:
        x = temp[temp["algorithm"] == algorithm]

        if not x.empty:
            plt.plot(
                x["n"],
                x["time_ms"],
                marker="o",
                label=algorithm
            )

    plt.xlabel("Input size n")
    plt.ylabel("Average time (ms)")
    plt.title("QuickSort pivot comparison - " + data_type)
    plt.legend()
    plt.tight_layout()

    plt.savefig(
        "graphs/quick_" + data_type + "_time.png"
    )

    plt.close()

# ---------- Stage 2 ----------
all_data = avg[avg["stage"] == "AllAlgorithms"]

algorithms = [
    "Bubble",
    "Insertion",
    "Merge",
    "Quick_Median3",
    "Heap",
    "Radix"
]

for data_type in ["random", "sorted", "reverse"]:
    temp = all_data[all_data["type"] == data_type]

    plt.figure()

    for algorithm in algorithms:
        x = temp[temp["algorithm"] == algorithm]

        if not x.empty:
            plt.plot(
                x["n"],
                x["time_ms"],
                marker="o",
                label=algorithm
            )

    plt.xlabel("Input size n")
    plt.ylabel("Average time (ms)")
    plt.title("Sorting algorithm comparison - " + data_type)
    plt.legend()
    plt.tight_layout()

    plt.savefig(
        "graphs/all_" + data_type + "_time.png"
    )

    plt.close()

# ---------- Comparisons vs time ----------
random_data = all_data[
    all_data["type"] == "random"
]

plt.figure()

for algorithm in algorithms:
    x = random_data[
        random_data["algorithm"] == algorithm
    ]

    if not x.empty:
        plt.plot(
            x["comparisons"],
            x["time_ms"],
            marker="o",
            label=algorithm
        )

plt.xlabel("Average comparisons")
plt.ylabel("Average time (ms)")
plt.title("Comparisons vs execution time - random input")
plt.legend()
plt.tight_layout()

plt.savefig("graphs/comparisons_vs_time.png")
plt.close()

print("Graphs created successfully in graphs/")
