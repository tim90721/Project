import sys
import csv
import collections
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

def collectDataUE(filename):
    latencies = {}

    with open(filename, newline='') as csvfile:
        rows = csv.reader(csvfile)
        next(rows)
        for row in rows:
            activeTiming = int(row[6]) * 10 + int(row[7])
            departedTiming = int(row[10]) * 10 + int(row[11])
            latency = departedTiming - activeTiming + 1
            latencies[int(row[0])] = latency
    
    latencies = collections.OrderedDict(sorted(latencies.items()))
    return latencies

def collectDataCell(filename):
    successUEs = []
    estimateUEs = []
    with open(filename, newline='') as csvfile:
        rows = csv.reader(csvfile)
        next(rows)
        for row in rows:
            successUEs.append(int(row[7]))
            estimateUEs.append(int(row[8]))
        del successUEs[-1]
        del estimateUEs[-1]

    return successUEs, estimateUEs

def plotDataUE(latencies, upperBound, filenameFig1 = None, subTitle = ""):
    newXticks = np.linspace(0, len(latencies), 11)
    newYticks = range(0, upperBound + 5, 5)
    fig = plt.figure(1)
    ax = plt.subplot(1, 1, 1)
    fig.subplots_adjust(top=0.85)
    plt.plot(range(len(latencies)), latencies.values(), 'r-')
    plt.xlabel("UE Index")
    plt.ylabel("Latency (ms)")
    plt.suptitle("Each UE Latency", fontsize=14, fontweight="bold")
    plt.title(subTitle, y=0.93)
    plt.axis([0, len(latencies), 0, upperBound])
    plt.xticks(newXticks)
    plt.yticks(newYticks)
    plt.grid(True)
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("700x500+50+50")
    #manager.window.SetPosition("+500+0")
    if filenameFig1:
        plt.savefig(filenameFig1)
    del newXticks
    del newYticks

def plotDataCell(successUEs, estimateUEs, filenameFig2 = None, subTitle = ""):
    #newXticks = np.linspace(0, len(successUEs), 11);
    #for i in range(len(newXticks)):
    #    newXticks[i] = newXticks[i] * 16
    #print(newXticks)
    fig = plt.figure(2)
    ax = plt.subplot(1, 1, 1)
    line1, = ax.plot([x * 16 for x in range(len(successUEs))], successUEs, 'g-*', label='Success UEs')
    line2, = ax.plot([x * 16 for x in range(len(estimateUEs))], estimateUEs, 'b-o', label='estimate UEs')
    ax.legend(loc="lower right")
    #ax.xaxis.set_major_locator(ticker.FixedLocator(newXticks))
    fig.subplots_adjust(top=0.85)
    plt.suptitle("Estimate UEs vs Actual Success UEs", fontsize=14, fontweight="bold")
    ax.set_title(subTitle, y=0.93)
    plt.xlabel("Subframe Index")
    plt.ylabel("Number of UEs")
    plt.axis([0, len(successUEs) * 16, 0, max([max(successUEs), max(estimateUEs)]) + 10])
    plt.grid(True)
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("700x500+750+50")
    if filenameFig2:
        plt.savefig(filenameFig2)
    #plt.xticks([newXticks, newXticks])
    #del newXticks

if __name__ == '__main__':
    print('number of input: {0}'.format(len(sys.argv)))
    
    print('list of argument')
    
    for i in range(len(sys.argv) - 1):
        print(sys.argv[i + 1])
    
    outputFolderName = sys.argv[1]
    ueFile = sys.argv[2]
    cellFile = sys.argv[3]
    prachConfig = sys.argv[4]
    simulationTime = sys.argv[5]
    arrivalRate = sys.argv[6]
    
    subTitle = "\nPrach Configuration Index: {0}\n".format(prachConfig) \
            + "Simulation Time: {0} ".format(str(int(simulationTime) / 10)) \
            + "UE Arrival Rate: {0}\n".format(arrivalRate)
    
    filenameFig1 = outputFolderName + "UE_latency"
    filenameFig2 = outputFolderName + "Estimate_UEs"
    print(filenameFig1)
    print(filenameFig2)
    
    ############################ collect data ############################
    latencies = collectDataUE(ueFile)
    upperBound = max(latencies.values())
    while (upperBound % 5) != 0:
        upperBound += 1
        
    successUEs, estimateUEs = collectDataCell(cellFile)
    ############################ collect data ############################
    
    ############################ plot data ############################
    plotDataUE(latencies, upperBound, filenameFig1, subTitle)
    plotDataCell(successUEs, estimateUEs, filenameFig2, subTitle)
    plt.show()
    ############################ plot data ############################
    
    del ueFile
    del cellFile
    del latencies
    del upperBound
