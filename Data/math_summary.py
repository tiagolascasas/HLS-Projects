import csv
import pandas as pd

fun_keep = ["source program"]
with open('MathAnalysis.csv', "r") as csvfile:
    reader_bm = csv.DictReader(csvfile)
    header = reader_bm.fieldnames

    # Get functions
    counts = {}
    for i in range(1, len(header)):
        counts[header[i]] = 0
    # Count occurrences for each benchmark
    n_bm = 0
    for row in reader_bm:
        n_bm += 1
        for fun in row.keys():
            if fun != 'source program':
                counts[fun] += int(row[fun])
    # Filter functions with 0 occurrences
    new_counts = {}
    for fun in counts.keys():
        if counts[fun] != 0:
            new_counts[fun] = counts[fun]
            fun_keep.append(fun)
    # Print function frequency summary
    print("Counts for each function across " + str(n_bm) +" benchmarks:")
    for fun in new_counts.keys():
        print(fun + ": " + str(new_counts[fun]))
    # Save in CSV
    with open("MathFunctionFrequency.csv", 'w', newline='') as csvfile:
        freq = "frequency across " + str(n_bm) + " benchmarks"
        header = ["function", freq]
        writer = csv.DictWriter(csvfile, fieldnames=header)
        writer.writeheader()
        for fun in new_counts.keys():
            writer.writerow({"function": fun, freq: str(new_counts[fun])})

# Save CSV with only functions with > 0 occurrences
f = pd.read_csv("MathAnalysis.csv")
new_f = f[fun_keep]
new_f.to_csv("MathAnalysisFiltered.csv", index=False)