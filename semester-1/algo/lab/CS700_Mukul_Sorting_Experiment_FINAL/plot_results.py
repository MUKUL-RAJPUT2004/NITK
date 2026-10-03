import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

Path("graphs").mkdir(exist_ok=True)

df = pd.read_csv("results/results.csv")

if df.empty:
    print("No results found. Run the C++ experiment first.")
    raise SystemExit

avg = (
    df.groupby(["algorithm", "input_type", "input_size"], as_index=False)
      .agg(time_ms=("time_ms", "mean"),
           comparisons=("comparisons", "mean"))
)

# QuickSort pivot comparison
quick = [
    "Quick - First Pivot",
    "Quick - Random Pivot",
    "Quick - Median of Three"
]

for input_type in ["random", "ascending", "descending"]:
    plt.figure(figsize=(9, 6))
    part = avg[avg["input_type"] == input_type]

    for algorithm in quick:
        x = part[part["algorithm"] == algorithm]
        if not x.empty:
            plt.plot(x["input_size"], x["time_ms"],
                     marker="o", label=algorithm)

    plt.xlabel("Input size (n)")
    plt.ylabel("Average time (ms)")
    plt.title("QuickSort Pivot Comparison - " + input_type)
    plt.legend()
    plt.grid(True, alpha=0.25)
    plt.tight_layout()
    plt.savefig(f"graphs/quick_{input_type}.png", dpi=150)
    plt.close()

# Overall comparison
comparison = [
    "Merge Sort",
    "Quick - Median of Three",
    "Heap Sort",
    "Radix Sort"
]

for input_type in ["random", "ascending", "descending"]:
    plt.figure(figsize=(9, 6))
    part = avg[avg["input_type"] == input_type]

    for algorithm in comparison:
        x = part[part["algorithm"] == algorithm]
        if not x.empty:
            plt.plot(x["input_size"], x["time_ms"],
                     marker="o", label=algorithm)

    plt.xlabel("Input size (n)")
    plt.ylabel("Average time (ms)")
    plt.title("Efficient Sorting Algorithm Comparison - " + input_type)
    plt.legend()
    plt.grid(True, alpha=0.25)
    plt.tight_layout()
    plt.savefig(f"graphs/overall_{input_type}.png", dpi=150)
    plt.close()

# Comparison count
part = avg[avg["input_type"] == "random"]

plt.figure(figsize=(9, 6))
for algorithm in comparison:
    x = part[part["algorithm"] == algorithm]
    if not x.empty:
        plt.plot(x["input_size"], x["comparisons"],
                 marker="o", label=algorithm)

plt.xlabel("Input size (n)")
plt.ylabel("Average comparisons")
plt.title("Comparison Count on Random Input")
plt.legend()
plt.grid(True, alpha=0.25)
plt.tight_layout()
plt.savefig("graphs/comparisons_random.png", dpi=150)
plt.close()

print("Graphs created in graphs/")
