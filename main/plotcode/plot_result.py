import sys
import csv
import collections
import numpy as np
import matplotlib.pyplot as plt

print('number of input: {0}'.format(len(sys.argv)))

print('list of argument')

for i in range(len(sys.argv) - 1):
    print(sys.argv[i + 1])

ueFile = sys.argv[1]
cellFile = sys.argv[2]

latencies = {}

with open(ueFile, newline='') as csvfile:
    rows = csv.reader(csvfile)
    next(rows)
    for row in rows:
        activeTiming = int(row[6]) * 10 + int(row[7])
        departedTiming = int(row[10]) * 10 + int(row[11])
        latency = departedTiming - activeTiming + 1
        latencies[int(row[0])] = latency

latencies = collections.OrderedDict(sorted(latencies.items()))

upperBound = max(latencies.values())
while (upperBound % 5) != 0:
    upperBound += 1
newXticks = np.linspace(0, len(latencies), 11)
newYticks = range(0, upperBound + 5, 5)
plt.plot(range(len(latencies)), latencies.values(), 'r-')
plt.xlabel("UE Index")
plt.ylabel("Latency (ms)")
plt.title("Each UE Latency")
plt.axis([0, len(latencies), 0, upperBound])
plt.xticks(newXticks)
plt.yticks(newYticks)
plt.grid(True)
plt.show()
del ueFile
del cellFile
del latencies
del upperBound
del newXticks
del newYticks
