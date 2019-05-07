import sys
import csv
import collections
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math

def avgSIBPeriodUELatency(latencies):
    total = 0
    sibPeriod = 160
    avg = []
    count = 0
    for profile in latencies.values():
        if profile['arrival'] == sibPeriod:
            avg.append(total / count)
            total = 0
            count = 0
            sibPeriod = sibPeriod + 160
        total = total + profile['latency']
        count = count + 1
    avg.append(total / count)
    return avg

def collectDataUE(filename):
    latencies = {}

    with open(filename, newline='') as csvfile:
        rows = csv.DictReader(csvfile)
        #next(rows)
        for row in rows:
            activeTiming = int(row['Active Frame']) * 10 + int(row['Active Subframe'])
            departedTiming = int(row['Departed Frame']) * 10 + int(row['Departed Subframe'])
            latency = departedTiming - activeTiming + 1
            latencies[int(row['UE ID'])] = {'arrival':activeTiming, 'latency':latency}
    
    latencies = collections.OrderedDict(sorted(latencies.items()))
    return latencies

def collectDataCell(filename):
    successUEs = []
    estimateUEs = []
    arrivalUEs = []
    participateUEs = []
    delta = []
    tau = []
    with open(filename, newline='') as csvfile:
        rows = csv.DictReader(csvfile)
        for row in rows:
            successUEs.append(int(row['Success UEs']))
            estimateUEs.append(int(row['Estimate UEs']))
            arrivalUEs.append(int(row['Arrival UEs']))
            participateUEs.append(int(row['Participate UEs']))
            delta.append(float(row['Total Channel Capacity']))
            tau.append(int(row['Tau']))
        del estimateUEs[-1]
        del delta[-1]
        del delta[0]
        del tau[-1]
        estimateUEs.insert(0, 0)
        tau.insert(0, tau[0])
        delta.insert(0, delta[0])
        delta.insert(len(delta), delta[-1])

    return arrivalUEs, participateUEs, successUEs, estimateUEs, delta, tau

def plotDataUE(latencies, upperBound, filenameFig1 = None, subTitle = ""):
    newXticks = np.linspace(0, len(latencies), 11)
    fig = plt.figure(1)
    fig.set_size_inches(9.375, 7.3)
    ax = plt.subplot(1, 1, 1)
    fig.subplots_adjust(top=0.85)
    plt.plot(range(len(latencies)), [x['latency'] for x in latencies.values()], 'r-')
    plt.xlabel("UE Index")
    plt.ylabel("Latency (ms)")
    plt.suptitle("Each UE Latency", fontsize=14, fontweight="bold")
    plt.title(subTitle)
    plt.axis([0, len(latencies), 0, upperBound + 5])
    plt.xticks(newXticks)
    plt.grid(True)
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("900x700+50+50")
    if filenameFig1:
        plt.savefig(filenameFig1)
    del newXticks

def plotDataCell(arrivalUEs, participateUEs, successUEs, estimateUEs, delta, filenameFig2 = None, subTitle = ""):
    fig = plt.figure(2)
    fig.set_size_inches(9.375, 7.3)
    ax = plt.subplot(1, 1, 1)
    line1, = ax.plot([x * 160 for x in range(len(successUEs))], successUEs, 'g-*', label='Success UEs')
    line2, = ax.plot([x * 160 for x in range(len(estimateUEs))], estimateUEs, 'b-o', label='Estimate UEs')
    line3, = ax.plot([x * 160 for x in range(len(arrivalUEs))], arrivalUEs, 'k-^', label='Arrival UEs')
    line4, = ax.plot([x * 160 for x in range(len(participateUEs))], participateUEs, 'r-D', label='Participate UEs')
    line5, = ax.plot([x * 160 for x in range(len(delta))], delta, 'm-D', label='Total Channel Capacity')
    ax.legend(loc="upper left")
    fig.subplots_adjust(top=0.85)
    plt.suptitle("UEs Condition & Esitimate UEs", fontsize=14, fontweight="bold")
    ax.set_title(subTitle)
    plt.xlabel("Subframe Index")
    plt.ylabel("Number of UEs")
    #plt.axis([0, len(successUEs) * 160, 0, max([max(successUEs), max(estimateUEs), max(arrivalUEs), max(participateUEs)]) + 10])
    plt.grid(True)
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("900x700+450+50")
    if filenameFig2:
        plt.savefig(filenameFig2)

def plotSIBLatencyAndTau(avgSIBlatencies, tau, filename=None):
    del tau[0]
    while len(tau) != len(avgSIBlatencies):
        del tau[-1]
    fig = plt.figure(3)
    fig.set_size_inches(9.375, 7.3)
    ax1 = plt.subplot(1, 1, 1)
    t = [x + 1 for x in range(len(tau))]
    ax1.plot(t, avgSIBlatencies, 'r-o')
    ax1.set_xlabel('SIB Period Index', fontsize=12)
    ax1.set_ylabel('Averge Latency (ms)', color='r', fontsize=12)
    ax1.tick_params('y', colors='r')

    ax2 = ax1.twinx()
    ax2.plot(t, tau, 'b-^')
    ax2.set_ylabel('RA Attemp Period (ms)', color='b', fontsize=12)
    ax2.tick_params('y', colors='b')
    fig.subplots_adjust(top=0.85)
    plt.suptitle("Each SIB Period UE Average Latency vs RA Attempt Period", fontsize=14, fontweight="bold")
    ax1.grid(True)
    ytop = 10 * (int(max([max(avgSIBlatencies), max(tau)]) / 10) + 1)
    ax1.set_ylim(0, ytop)
    ax2.set_ylim(0, ytop)
    #fig.tight_layout()
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("900x700+1050+50")
    if filename:
        plt.savefig(filename)

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
    arrivalMode = sys.argv[6]
    if arrivalMode == "uniform":
        arrivalRate = sys.argv[7]
    else:
        totalUE = sys.argv[7]
    
    subTitle = "Prach Configuration Index: {0}, ".format(prachConfig) \
            + "Simulation Time: {0}s\n".format(str(int(simulationTime) / 1000)) \
            + "Arrival Mode: {0}, ".format(arrivalMode)
    if arrivalMode == "uniform":
        subTitle = subTitle + "Arrival Rate: {0} ".format(arrivalRate)
    else:
        subTitle = subTitle + "Total UE: {0} ".format(totalUE)

    filenameFig1 = outputFolderName + "UE_latency"
    filenameFig2 = outputFolderName + "Estimate_UEs"
    filenameFig3 = outputFolderName + "AvgLatency_and_Tau"
    print(filenameFig1)
    print(filenameFig2)
    
    ############################ collect data ############################
    latencies = collectDataUE(ueFile)
    avgSIBlatencies = avgSIBPeriodUELatency(latencies)
    upperBound = max([x['latency'] for x in latencies.values()])
    while (upperBound % 5) != 0:
        upperBound += 1
        
    arrivalUEs, participateUEs, successUEs, estimateUEs, delta, tau = collectDataCell(cellFile)
    ############################ collect data ############################
    
    ############################ plot data ############################
    plotDataUE(latencies, upperBound, filenameFig1, subTitle)
    plotDataCell(arrivalUEs, participateUEs, successUEs, estimateUEs, delta, filenameFig2, subTitle)
    plotSIBLatencyAndTau(avgSIBlatencies, tau, filenameFig3)
    plt.show()
    ############################ plot data ############################
    
    del ueFile
    del cellFile
    del latencies
    del upperBound
    del arrivalUEs
    del participateUEs
    del successUEs
    del estimateUEs
    del delta
    del avgSIBlatencies
