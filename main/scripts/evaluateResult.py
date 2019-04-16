#/usr/bin/python3
import os
import csv
import matplotlib.pyplot as plt
import numpy as np
from plot_result import collectDataUE

figureCount = 0

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

def plotAverageResult(average, filename=""):
    global figureCount
    fig = plt.figure(figureCount)
    figureCount = figureCount + 1
    fig.subplots_adjust(top = 0.85)
    ax = plt.subplot(1, 1, 1)
    plt.plot(average.keys(), average.values(), 'b-o')
    plt.xlabel("RA Subframe Period")
    plt.ylabel("Average Latency (ms)")
    plt.suptitle("Average UE Latency vs RA Subframe Period", fontsize=14, fontweight="bold")
    plt.axis([0, max(average.keys()) + 2, 0, max(average.values()) + 10])
    plt.grid(True)
    if filename:
        plt.savefig(filename)
    #plt.show()

def plotLantencyCDF(latency, prachIndex, simulationTime, arrivalRate, saveFolderName=""):
    global figureCount
    subTitle = "Prach Configuration Index: {0}\n".format(prachIndex) \
            + "Simulation Time: {0} ".format(str(int(simulationTime) / 1000)) \
            + "UE Arrival Rate: {0}\n".format(arrivalRate)
    filenameFig = "CDF_prach-{0}_simu-{1}_arrival-{2}".format(prachIndex,
            simulationTime,
            arrivalRate)

    X = np.linspace(min(latency), max(latency), max(latency) - min(latency))
    hist, bin_edges = np.histogram(latency, bins=max(latency) - min(latency), density=True)
    hist = np.cumsum(hist)

    fig = plt.figure(figureCount)
    figureCount = figureCount + 1
    fig.subplots_adjust(top=0.85)
    ax = plt.subplot(1, 1, 1)
    plt.plot(X, hist, 'b-')
    plt.xlabel("Latency (ms)")
    plt.ylabel("CDF")
    plt.suptitle("UE Latency CDF", fontsize=14, fontweight="bold")
    ax.set_title(subTitle, y=0.93)
    plt.axis([min(latency), max(latency), 0, 1.1])
    plt.grid(True)
    if saveFolderName:
        plt.savefig(saveFolderName + filenameFig)
    del X
    del hist
    del bin_edges

ueFile = 'UE.csv'
cellFile = 'Cell.csv'
resultSourceFolder = "./candidateResult/"
savefigureName = "result.png"

folderName = [name for name in os.listdir(resultSourceFolder)]
folderName.remove(savefigureName)

############ get parameters ############
prachIndex = [name.split("prach-")[1] for name in folderName]
prachIndex = [name.split("_")[0] for name in prachIndex]
simulationTime = [name.split("simu-")[1] for name in folderName]
simulationTime = [name.split("_")[0] for name in simulationTime]
arrivalRate = [name.split("arrival-")[1] for name in folderName]
arrivalRate = [name.split("_")[0] for name in arrivalRate]
############ get parameters ############

avgs = {}
latencies = []

while(len(prachIndex) > 0):
    maxIndex = prachIndex.index(max(prachIndex))
    filename = resultSourceFolder + folderName[maxIndex] + "/" + ueFile
    latency = collectDataUE(filename)
    avgs[getSubframePeriod(int(prachIndex[maxIndex]))] = np.mean(list(latency.values()))
    plotLantencyCDF(list(latency.values()), prachIndex[maxIndex], simulationTime[maxIndex], arrivalRate[maxIndex], resultSourceFolder)
    #print(prachIndex[maxIndex])
    #print(folderName[maxIndex])
    #print(filename)
    #print(len(latency))
    del prachIndex[maxIndex]
    del simulationTime[maxIndex]
    del arrivalRate[maxIndex]
    del folderName[maxIndex]

print(avgs)
plotAverageResult(avgs, resultSourceFolder + savefigureName)
plt.show()
del avgs
