import matplotlib
matplotlib.use("Agg")

import csv
import os
import matplotlib.pyplot as plt

csv_path = "readings.csv"
if not os.path.exists(csv_path):
    raise FileNotFoundError("File 'readings.csv' not found")

days, sys, dias = [], [], []

with open(csv_path, newline="", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        days.append(int(row["day"]))
        sys.append(int(row["sys"]))
        dias.append(int(row["dias"]))

if not days:
    raise ValueError("In 'readings.csv' are no data.")

out_dir = "out"
os.makedirs(out_dir, exist_ok=True)

plt.figure()
plt.plot(days, sys, marker="o", label="SYS")
plt.plot(days, dias, marker="o", label="DIAS")
plt.title("Blood Pressure Over Time")
plt.xlabel("Day")
plt.ylabel("mmHg")
plt.legend()
out_file = os.path.join(out_dir, "bp_timeseries.png")
plt.savefig(out_file, dpi=150, bbox_inches="tight")
plt.close()

print(f"Done! Plot is here: {out_file}")
