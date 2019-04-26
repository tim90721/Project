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

def plotLantencyCDF(latency, prachIndex, simulationTime, arrivalMode, arrival, saveFolderName=""):
    global figureCount
    subTitle = "Prach Configuration Index: {0}, ".format(prachIndex) \
            + "Simulation Time: {0}\n".format(str(int(simulationTime) / 1000)) \
            + "Arrival Mode: {0}, ".format(arrivalMode)
    if arrivalMode == "uniform":
        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
    else:
        subTitle = subTitle + "Totle UE: {0}".format(arrival)
    filenameFig = "CDF_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prachIndex,
            simulationTime,
            arrivalMode,
            arrival)

    latency.insert(0, 0)
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
    ax.set_title(subTitle)
    plt.axis([0, max(latency), 0, 1.1])
    plt.grid(True)
    if saveFolderName:
        plt.savefig(saveFolderName + filenameFig)
    del X
    del hist
    del bin_edges

ueFile = 'UE.csv'
cellFile = 'Cell.csv'
resultSourceFolder = "./candidateResult/"
savefigureNameUniform = "result_uniform.png"
savefigurenameBeta = "result_beta.png"

folderName = [name for name in os.listdir(resultSourceFolder)]
folderName = [name for name in folderName if "png" not in name]

#if savefigureName in folderName:
#    folderName.remove(savefigureName)

############# get parameters ############
prachIndex = [name.split("prach-")[1] for name in folderName]
prachIndex = [name.split("_")[0] for name in prachIndex]
simulationTime = [name.split("simu-")[1] for name in folderName]
simulationTime = [name.split("_")[0] for name in simulationTime]
arrivalMode = [name.split("_")[4] for name in folderName]
arrival = [name.split("_")[5] for name in folderName]
arrival = [name.split("-")[1] for name in arrival]
#for i in range(len(folderName)):
#    print(folderName[i])
#    print(arrivalMode[i])
#    print(arrival[i])
############ get parameters ############

avgs_uniform = {}
avgs_beta = {}
latencies = []

while(len(prachIndex) > 0):
    maxIndex = prachIndex.index(max(prachIndex))
    filename = resultSourceFolder + folderName[maxIndex] + "/" + ueFile
    latency = collectDataUE(filename)
    if arrivalMode[maxIndex] == "uniform":
        avgs_uniform[getSubframePeriod(int(prachIndex[maxIndex]))] = np.mean(list(latency.values()))
    else:
        avgs_beta[getSubframePeriod(int(prachIndex[maxIndex]))] = np.mean(list(latency.values()))

    plotLantencyCDF(list(latency.values()), prachIndex[maxIndex], simulationTime[maxIndex], arrivalMode[maxIndex], arrival[maxIndex], resultSourceFolder)
    #print(prachIndex[maxIndex])
    #print(folderName[maxIndex])
    #print(filename)
    #print(len(latency))
    del prachIndex[maxIndex]
    del simulationTime[maxIndex]
    del arrivalMode[maxIndex]
    del arrival[maxIndex]
    del folderName[maxIndex]

print(avgs_uniform)
plotAverageResult(avgs_uniform, resultSourceFolder + savefigureNameUniform)
plotAverageResult(avgs_beta, resultSourceFolder + savefigurenameBeta)
plt.show()
del avgs_uniform
