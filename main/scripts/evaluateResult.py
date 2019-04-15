#/usr/bin/python3
import os
import csv
import matplotlib.pyplot as plt
import numpy as np
from plot_result import collectDataUE

def getSubframePeriod(prachIndex):
    if prachIndex == 27:
        return 1
    elif prachIndex == 25:
        return 2
    elif prachIndex == 22:
        return 3.5
    elif prachIndex == 19:
        return 5
    elif prachIndex == 16:
        return 10

def plotAverageResult(average):
    fig = plt.figure(1)
    fig.subplots_adjust(top = 0.85)
    ax = plt.subplot(1, 1, 1)
    plt.plot(average.keys(), average.values(), 'b-o')
    plt.xlabel("RA Subframe Period")
    plt.ylabel("Average Latency (ms)")
    plt.suptitle("Average UE Latency vs RA Subframe Period", fontsize=14, fontweight="bold")
    plt.axis([0, max(average.keys()) + 2, 0, max(average.values()) + 10])
    plt.grid(True)
    plt.show()

ueFile = 'UE.csv'
cellFile = 'Cell.csv'
resultSourceFolder = "./candidateResult/"

folderName = [name for name in os.listdir(resultSourceFolder)]

prachIndex = [name.split("prach-")[1] for name in folderName]
prachIndex = [name.split("_")[0] for name in prachIndex]

avgs = {}

while(len(prachIndex) > 0):
    maxIndex = prachIndex.index(max(prachIndex))
    filename = resultSourceFolder + folderName[maxIndex] + "/" + ueFile
    latencies = collectDataUE(filename)
    avgs[getSubframePeriod(int(prachIndex[maxIndex]))] = np.mean(list(latencies.values()))
    #print(prachIndex[maxIndex])
    #print(folderName[maxIndex])
    #print(filename)
    #print(len(latencies))
    del prachIndex[maxIndex]
    del folderName[maxIndex]
    del latencies

print(avgs)
plotAverageResult(avgs)
del avgs
