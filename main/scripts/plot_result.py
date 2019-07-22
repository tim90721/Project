import os
import sys
import csv
import collections
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math

#############################
# plot the *newest* result from the result folder
#############################

line_width = 3.0
marker_size = 7.0
label_font_size = 20
title_font_size = 24
legend_font_size = 16

plot_optimized = False

def getSubframePeriod(prachIndex):
    if type(prachIndex) is not int:
        prachIndex = int(prachIndex)
    if prachIndex == 27:
        return 1
    elif prachIndex == 25:
        return 2
    elif prachIndex == 22:
        return 3
    elif prachIndex == 19:
        return 5
    elif prachIndex == 16:
        return 10

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
    timing = []
    if plot_optimized:
        tauOp = []
        deltaOp = []
    with open(filename, newline='') as csvfile:
        rows = csv.DictReader(csvfile)
        for row in rows:
            timing.append(int(row['Current Frame']) * 10 + int(row['Current Subframe']))
            successUEs.append(int(row['Success UEs']))
            estimateUEs.append(int(row['Estimate UEs']))
            arrivalUEs.append(int(row['Arrival UEs']))
            participateUEs.append(int(row['Participate UEs']))
            delta.append(float(row['Total Channel Capacity']))
            tau.append(int(row['Tau']))
            if plot_optimized:
                deltaOp.append(float(row['Total Channel Capacity Optimized']))
                tauOp.append(float(row['Tau Optimized']))
#        del estimateUEs[-1]
#        del delta[-1]
        del delta[0]
        del tau[-1]
#        estimateUEs.insert(0, 0)
        tau.insert(0, tau[0])
#        delta.insert(0, delta[0])
        delta.insert(len(delta), delta[-1])

    if plot_optimized:
        return timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, tau, deltaOp, tauOp
    return timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, tau

def plotDataUE(latencies, upperBound, filenameFig1 = None, subTitle = ""):
    newXticks = np.linspace(0, len(latencies), 11)
    fig = plt.figure(1)
    fig.set_size_inches(9.375, 7.3)
    ax = plt.subplot(1, 1, 1)
    #fig.subplots_adjust(top=0.83)
    plt.plot(range(len(latencies)), [x['latency'] for x in latencies.values()], 'r-')
    plt.xlabel("UE Index", fontsize=label_font_size)
    plt.ylabel("Latency (ms)", fontsize=label_font_size)
    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
        label.set_fontsize(16)
    #plt.suptitle("Each UE Latency", fontweight="bold", fontsize=title_font_size)
    #plt.title(subTitle, fontsize=title_font_size)
    plt.axis([0, len(latencies), 0, upperBound + 5])
    plt.xticks(newXticks)
    plt.grid(True)
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("900x700+50+50")
    if filenameFig1:
        plt.savefig(filenameFig1)
        plt.close()
    del newXticks

def plotDataCell(timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, deltaOp=None, filenameFig2 = None, subTitle = ""):
    maxNum = max([max(arrivalUEs), 
        max(participateUEs), 
        max(successUEs), 
        max(estimateUEs), 
        max(delta)])
    if plot_optimized and (deltaOp is not None):
        maxNum = max(maxNum, max(deltaOp))
    power = math.floor(math.log(maxNum, 10))
    ylimit = math.floor(maxNum / pow(10, power))
    ylimit = (ylimit + 2) * pow(10, power)

    fig = plt.figure(2)
    fig.set_size_inches(9.375, 7.3)
    ax = plt.subplot(1, 1, 1)
    line1, = ax.plot(timing, successUEs, 'g-s', label='Success UEs', linewidth=line_width, markersize=marker_size + 7)
    line2, = ax.plot(timing, estimateUEs, 'c-o', label='Estimate UEs', linewidth=line_width, markersize=marker_size + 3)
    line3, = ax.plot(timing, arrivalUEs, 'k-^', label='Arrival UEs', linewidth=line_width, markersize=marker_size + 7, fillstyle="none", markeredgewidth=3.0)
    line4, = ax.plot(timing, participateUEs, 'r-v', label='Participate UEs', linewidth=line_width, markersize=marker_size + 7, fillstyle="none", markeredgewidth=3.0)
    line5, = ax.plot(timing, delta, 'm-D', label='Total Channel Capacity', linewidth=line_width, markersize=marker_size + 2)
    if plot_optimized:
        line6, = ax.plot(timing, deltaOp, 'b-H', label='Optimized Channel Capacity', linewidth=line_width, markersize=marker_size + 10, fillstyle="none", markeredgewidth=3.0)
    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
        label.set_fontsize(16)
    ax.legend(loc="upper left", fontsize=legend_font_size)
    ax.set_ylim(0, ylimit)
    #fig.subplots_adjust(top=0.83)
    #plt.suptitle("UEs Condition & Esitimate UEs", fontsize=title_font_size, fontweight="bold")
    #plt.suptitle("Beta Distribution Arrival", fontsize=14, fontweight="bold")
    #ax.set_title(subTitle, fontsize=title_font_size)
    plt.xlabel("Subframe Index", fontsize=label_font_size)
    plt.ylabel("Number of UEs", fontsize=label_font_size)
    #plt.axis([0, len(successUEs) * 160, 0, max([max(successUEs), max(estimateUEs), max(arrivalUEs), max(participateUEs)]) + 10])
    plt.grid(True)
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("900x700+450+50")
    if filenameFig2:
        plt.savefig(filenameFig2)
        plt.close()

def plotSIBLatencyAndTau(avgSIBlatencies, tau, filename=None):
    del tau[0]
    while len(tau) != len(avgSIBlatencies):
        del tau[-1]
    fig = plt.figure(3)
    fig.set_size_inches(9.375, 7.3)
    ax1 = plt.subplot(1, 1, 1)
    t = [x + 1 for x in range(len(tau))]
    ax1.plot(t, avgSIBlatencies, 'r-o', linewidth=line_width, markersize=marker_size + 3)
    ax1.set_xlabel('SIB Period Index', fontsize=label_font_size)
    ax1.set_ylabel('Averge Latency (ms)', color='r', fontsize=label_font_size)
    ax1.tick_params('y', colors='r')

    ax2 = ax1.twinx()
    ax2.plot(t, tau, 'b-^', linewidth=line_width, markersize=marker_size + 6, fillstyle="none", markeredgewidth=3.0)
    ax2.set_ylabel('RA Attemp Period (ms)', color='b', fontsize=label_font_size)
    ax2.tick_params('y', colors='b')
    #fig.subplots_adjust(top=0.8)
    #plt.suptitle("Each SIB Period UE Average Latency\nvs\nRA Attempt Period", fontsize=title_font_size, fontweight="bold")
    ax1.grid(True)
    ytop = 10 * (int(max([max(avgSIBlatencies), max(tau)]) / 10) + 1)
    ax1.set_ylim(0, ytop)
    ax2.set_ylim(0, ytop)
    for label in (ax1.get_xticklabels() + ax1.get_yticklabels()):
        label.set_fontsize(16)
    for label in (ax2.get_xticklabels() + ax2.get_yticklabels()):
        label.set_fontsize(16)
    #fig.tight_layout()
    manager = plt.get_current_fig_manager()
    manager.window.wm_geometry("900x700+1050+50")
    if filename:
        plt.savefig(filename)
        plt.close()

if __name__ == '__main__':
    command = sys.argv
    if 'plot_op' in command:
        plot_optimized = True
        print("plot optimized")
    #print(plot_optimized)
    ueFile = 'UE.csv'
    cellFile = 'Cell.csv'
    resultSourceFolder = "./result/"
    
    dirs = [(resultSourceFolder + d) for d in os.listdir(resultSourceFolder) if os.path.isdir(resultSourceFolder + d)]
    folderName = max(dirs, key=os.path.getmtime)
    print(folderName)

    prachConfig = folderName.split("prach-")[1]
    prachConfig = prachConfig.split("_")[0]
    simulationTime = folderName.split("simu-")[1]
    simulationTime = simulationTime.split("_")[0]
    arrivalMode = folderName.split("_")[4]
    arrival = folderName.split("_")[5]
    arrival = arrival.split("-")[1]
    if arrivalMode == "uniform":
        arrivalRate = arrival
    else:
        totalUE = arrival
    #print("prach:" + prachIndex)
    #print("simu:" + simulationTime)
    #print("arrival mode:" + arrivalMode)
    #print("arrival:" + arrival)

    subTitle = "RA Subframe Period: {0}ms, ".format(getSubframePeriod(prachConfig)) \
            + "Simulation Time: {0}s\n".format(str(int(simulationTime))) \
            + "Arrival Mode: {0}, ".format(arrivalMode)
    #subTitle = "Simulation Time: {0}s\n".format(str(int(simulationTime) / 1000)) \
    #        + "Arrival Mode: {0}, ".format(arrivalMode)
    if arrivalMode == "uniform":
        subTitle = subTitle + "Arrival Rate: {0} ".format(arrivalRate)
    else:
        subTitle = subTitle + "Total UE: {0} ".format(totalUE)

    filenameFig1 = folderName + "/" + "UE_latency"
    filenameFig2 = folderName + "/" + "Estimate_UEs"
    filenameFig3 = folderName + "/" + "AvgLatency_and_Tau"
    ueFile = folderName + "/" + ueFile
    cellFile = folderName + "/" + cellFile
    print(filenameFig1)
    print(filenameFig2)
    
    ############################ collect data ############################
    latencies = collectDataUE(ueFile)
    avgSIBlatencies = avgSIBPeriodUELatency(latencies)
    upperBound = max([x['latency'] for x in latencies.values()])
    while (upperBound % 5) != 0:
        upperBound += 1
        
    if plot_optimized:
        timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, tau, deltaOp, tauOp = collectDataCell(cellFile)
    else:
        timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, tau = collectDataCell(cellFile)
    print(timing)
    ############################ collect data ############################
    
    ############################ plot data ############################
    plotDataUE(latencies, upperBound, filenameFig1, subTitle)
    if plot_optimized:
        plotDataCell(timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, deltaOp, filenameFig2, subTitle)
    else:
        plotDataCell(timing, arrivalUEs, participateUEs, successUEs, estimateUEs, delta, None, filenameFig2, subTitle)
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
    del timing
    if plot_optimized:
        del deltaOp
        del tauOp
