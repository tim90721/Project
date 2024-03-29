import os
import csv
import matplotlib.pyplot as plt
import numpy as np
import math
from plot_result import collectDataUE, getSubframePeriod
from evaluateResult import collectCellMsg1FDM, getPreambleLength
from math import log


#######################
# plot each tau_threshold for each prach-configurationIndex 
# uniform and beta distribution result
#######################

# plot source folder organization
#
# candidateResult - ./10/
#                      | each prach configuration with uniform and beta
#
#                   ./20/
#                      | each prach configuration with uniform and beta
#
#                   ./40/
#                      | each prach configuration with uniform and beta
#
#                   ./80/
#                      | each prach configuration with uniform and beta
#
#                   ./160/
#                      | each prach configuration with uniform and beta

figureCount = 0

line_width = 3.0
marker_size = 10.0
label_font_size = 20
title_font_size = 24
legend_font_size = 16

def findCandidateFolder(targetPrach, targetArrival, folderName):
    candidateIndex = [index for index in range(len(folderName)) if "prach-"+targetPrach in folderName[index]]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if targetArrival in folderName[candidateIndex[index]]]
    #print(folderName)
    #print(candidateIndex)
    #print("target prach: ", targetPrach)
    #print("target arrival: ", targetArrival)
    #print("candidate folder: ", [folderName[candidateIndex[index]] for index in range(len(candidateIndex))])
    return candidateIndex[0]

def findCandidate(targetTau, targetPrach, targetArrival, targetSimulation, datas):
    candidateIndex = [index for index in range(len(datas)) if datas[index]['tau'] == targetTau]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if datas[candidateIndex[index]]['prachIndex'] == targetPrach]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if datas[candidateIndex[index]]['arrivalMode'] == targetArrival]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if datas[candidateIndex[index]]['simulationTime'] == targetSimulation]
    #print(candidateIndex)
    return candidateIndex[0]

def collectDataCell(filename):
    preambleSCS, timing, msg1FDM = collectCellMsg1FDM(filename)
    delta = []
    ssbPerRAO = []
    tau = []
    
    with open(filename, newline='') as csvfile:
        rows = csv.DictReader(csvfile)
        for row in rows:
            nBeams = row['Total Beams']
            delta.append(float(row['Total Channel Capacity']))
            ssbPerRAO.append(float(row['SSB per RAO']))
            tau.append(int(row['Tau']))
        del delta[-1]
        del delta[0]
        del tau[-1]
        delta.insert(0, delta[0])
        delta.insert(len(delta), delta[-1])
        tau.insert(0, tau[0])
    return nBeams, timing, preambleSCS, msg1FDM, ssbPerRAO, delta, tau


def plotLantencyCDF(uedatas, saveFolderName=""):
    print("Plotting Latency CDF...")
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                #fig.subplots_adjust(top=0.83)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Latency (ms)", fontsize=label_font_size)
                plt.ylabel("CDF",fontsize=label_font_size)
                #plt.suptitle("UE Latency CDF", fontsize=title_font_size, fontweight="bold")
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), uedatas)
                    data = uedatas[candidateIndex]
                    latency = data['latency']
                    arrival = data['arrival']
                    subTitle = "RA Subframe Period: {0}ms Simulation Time: {1}s\n".format(str(getSubframePeriod(prach)), str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    #ax.set_title(subTitle, fontsize=title_font_size)
                    
                    latency.insert(0, 0)
                    X = np.linspace(min(latency), max(latency), max(latency) - min(latency))
                    hist, bin_edges = np.histogram(latency, bins=max(latency) - min(latency), density=True)
                    hist = np.cumsum(hist)

                    plt.plot(X, hist, label=r"$\tau\ Threshold$="+str(tau), linewidth=line_width)
                    ax.legend(loc="lower right", fontsize=legend_font_size)
                    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
                        label.set_fontsize(16)
                filenameFig = "latency_CDF_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                plt.axis([0, max(latency), 0, 1.1])
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()
                del X
                del hist
                del bin_edges

def plotCellMsg1FDM(celldatas, saveFolderName=""):
    print("Plotting Msg1FDM...")
    global figureCount
    newYTick = [fdm*celldatas[0]['preambleLength']*float(celldatas[0]['preambleSCS'])/1000 for fdm in [1, 2, 4, 8]]
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                #fig.subplots_adjust(top=0.83)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=label_font_size)
                plt.ylabel("Preamble Occupied Bandwidth (MHz)", fontsize=label_font_size)
                #plt.suptitle(r"RA Used Bandwidth For Each $\tau$ Threshold", fontsize=title_font_size, fontweight="bold")
                plt.yticks(newYTick)
                i = 0
                attr = ['b-^', 'r-o', 'm-D', 'c-s', 'g-p']
                maxTiming = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "RA Subframe Period: {0}ms".format(str(getSubframePeriod(prach))) \
                            + " Simulation Time: {0}s\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    #ax.set_title(subTitle, fontsize=title_font_size)
                    
                    preambleBW = [fdm*data['preambleLength']*float(data['preambleSCS'])/1000 for fdm in data['msg1FDM']]
                    maxTiming = max([maxTiming, max(data['timing'])])
                    if i == 3:
                        ax.plot(data['timing'], preambleBW, attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 3, fillstyle="none", markeredgewidth=3.0)
                    elif i == 2:
                        ax.plot(data['timing'], preambleBW, attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 2, fillstyle="none", markeredgewidth=4.0)
                    elif i == 1:
                        ax.plot(data['timing'], preambleBW, attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 2)
                    elif i == 0:
                        ax.plot(data['timing'], preambleBW, attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 9)
                    else:
                        ax.plot(data['timing'], preambleBW, attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size)
                    i = i + 1
                    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
                        label.set_fontsize(16)
                filenameFig = "RA_Used_BW_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                xtick = math.ceil(maxTiming / 160)
                xtick = [(x * 160) for x in range(xtick + 1)]
                ax.legend(loc="upper left", fontsize=legend_font_size, ncol=2)
                ax.set_xlim(0, maxTiming)
                ax.set_ylim(0, math.ceil((max(newYTick) * 2) / 10) * 10)
                plt.xticks(xtick)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()
                    
def plotCellSSBPerRAO(celldatas, saveFolderName=""):
    print("Plotting SSB per RAO...")
    global figureCount
    newYTick = [0.125, 0.25, 0.5, 1, 2, 4, 8, 16]
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                #fig.subplots_adjust(top=0.83)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=label_font_size)
                plt.ylabel(r"SSB Per RAO $S_{RAO}$", fontsize=label_font_size)
                #plt.suptitle(r"Number of SSB Per RAO $S_{RAO}$ For Each $\tau$ Threshold", fontsize=title_font_size, fontweight="bold")
                plt.yticks(newYTick)
                i = 0
                attr = ['b-^', 'r-o', 'm-D', 'c-s', 'g-v']
                maxTiming = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "RA SubframePeriod: {0}ms".format(str(getSubframePeriod(prach))) \
                            + " Simulation Time: {0}s\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    #ax.set_title(subTitle, fontsize=title_font_size)
                    
                    maxTiming = max([maxTiming, max(data['timing'])])
                    if i == 4:
                        ax.plot(data['timing'], data['ssbPerRAO'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 9, fillstyle="none", markeredgewidth=3.0)
                    elif i == 2:
                        ax.plot(data['timing'], data['ssbPerRAO'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 3, fillstyle="none", markeredgewidth=3.0)
                    elif i == 1:
                        ax.plot(data['timing'], data['ssbPerRAO'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 5)
                    elif i == 0:
                        ax.plot(data['timing'], data['ssbPerRAO'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 7)
                    else:
                        ax.plot(data['timing'], data['ssbPerRAO'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size)
                    i = i + 1
                    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
                        label.set_fontsize(16)
                filenameFig = "S_RAO_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                xtick = math.ceil(maxTiming / 160)
                xtick = [(x * 160) for x in range(xtick + 1)]
                ax.legend(loc="upper left", fontsize=legend_font_size)
                ax.set_xlim(0, maxTiming)
                ax.set_ylim(newYTick[0], newYTick[-1])
                ax.set_yscale('log', basey=2)
                plt.xticks(xtick)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()

def plotCellDelta(celldatas, saveFolderName=""):
    print("Plotting Channel Capacity...")
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                #fig.subplots_adjust(top=0.83)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=label_font_size)
                plt.ylabel(r"Channel Capacity $\delta$", fontsize=label_font_size)
                #plt.suptitle(r"Channel Capacity $\delta$ For Each $\tau$ Threshold", fontsize=title_font_size, fontweight="bold")
                i = 0
                attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-v']
                maxTiming = 0
                maxDelta = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "RA Subframe Period: {0}ms".format(str(getSubframePeriod(prach))) \
                            + " Simulation Time: {0}s\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    #ax.set_title(subTitle, fontsize=title_font_size)
                    
                    maxTiming = max([maxTiming, max(data['timing'])])
                    maxDelta = max([maxDelta, max(data['delta'])])
                    if i == 4:
                        ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 9, fillstyle="none", markeredgewidth=3.0)
                    elif i == 0:
                        ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 7)
                    elif i == 1:
                        ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 5)
                    elif i == 2:
                        ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 9, fillstyle="none", markeredgewidth=3.0)
                    elif i == 3:
                        ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 7)

                    else:
                        ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size)
                    i = i + 1
                    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
                        label.set_fontsize(16)
                filenameFig = "Delta_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                xtick = math.ceil(maxTiming / 160)
                xtick = [(x * 160) for x in range(xtick + 1)]
                ax.legend(loc="upper left", fontsize=legend_font_size, ncol=2)
                ax.set_xlim(0, maxTiming)
                exponential = math.floor(log(maxDelta, 10))
                coef = maxDelta / pow(10, exponential)
                maxDelta = (coef * 2) * pow(10, exponential)
                ax.set_ylim(0, maxDelta)
                plt.xticks(xtick)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()

def plotCellTau(celldatas, saveFolderName=""):
    print("Plotting Tau...")
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                #fig.subplots_adjust(top=0.83)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=label_font_size)
                plt.ylabel(r"RA Attempt Period $\tau$", fontsize=label_font_size)
                #plt.suptitle(r"RA Attempt Period $\tau$ For Each $\tau$ Threshold", fontsize=title_font_size, fontweight="bold")
                i = 0
                attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-v']
                maxTiming = 0
                maxTau = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "RA Subframe Period: {0}".format(str(getSubframePeriod(prach))) \
                            + " Simulation Time: {0}\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    #ax.set_title(subTitle, fontsize=title_font_size)
                    
                    maxTiming = max([maxTiming, max(data['timing'])])
                    maxTau = max([maxTau, max(data['RA attempt period'])])
                    if i == 0:
                        ax.plot(data['timing'], data['RA attempt period'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 7)
                    elif i == 2:
                        ax.plot(data['timing'], data['RA attempt period'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 7, fillstyle="none", markeredgewidth=3.0)
                    elif i == 1:
                        ax.plot(data['timing'], data['RA attempt period'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 5)
                    elif i == 3:
                        ax.plot(data['timing'], data['RA attempt period'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size + 3)
                    else:
                        ax.plot(data['timing'], data['RA attempt period'], attr[i], label=r'$\tau\ Threshold$='+str(tau), linewidth=line_width, markersize=marker_size)
                    i = i + 1
                    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
                        label.set_fontsize(16)
                filenameFig = "RA_attempt_periodprach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                xtick = math.ceil(maxTiming / 160)
                xtick = [(x * 160) for x in range(xtick + 1)]
                ax.legend(loc="upper left", fontsize=legend_font_size, ncol=2)
                ax.set_xlim(0, maxTiming)
                ax.set_ylim(0, 220)
                #exponential = math.floor(log(maxTau, 10))
                #coef = maxTau / pow(10, exponential)
                #maxTau = (coef + 1) * pow(10, exponential)
                #ax.set_ylim(0, maxTau)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()

print("Collecting Datas...")
resultSourceFolder = "./candidateResult/"
folderNameUniform = "uniform/"
folderNameBeta = "beta/"

ueFile = "UE.csv"
cellFile = "Cell.csv"

if not os.path.exists(resultSourceFolder + folderNameUniform):
    os.makedirs(resultSourceFolder + folderNameUniform)
if not os.path.exists(resultSourceFolder + folderNameBeta):
    os.makedirs(resultSourceFolder + folderNameBeta)

folderTau = [name for name in os.listdir(resultSourceFolder)]
folderTau = [name for name in folderTau if "png" not in name]
folderTau.remove('beta')
folderTau.remove('uniform')
folderTau = [int(name) for name in folderTau]
folderTau.sort()
#print(folderTau)

folderName = {}
prachIndex = {}
simulationTime = {}
arrivalMode = {}
arrival = {}
for i in folderTau:
    folderName[i] = [name for name in os.listdir(resultSourceFolder + str(i))]
    prachIndex[i] = [name.split("prach-")[1] for name in folderName[i]]
    prachIndex[i] = [name.split("_")[0] for name in prachIndex[i]]
    simulationTime[i] = [name.split("simu-")[1] for name in folderName[i]]
    simulationTime[i] = [name.split("_")[0] for name in simulationTime[i]]
    arrivalMode[i] = [name.split("_")[4] for name in folderName[i]]
    arrival[i] = [name.split("_")[5] for name in folderName[i]]
    arrival[i] = [name.split("-")[1] for name in arrival[i]]
#print(folderName)
#print(prachIndex)
#print(simulationTime)
#print(arrivalMode)
#print(arrival)

tempPrach = prachIndex[10].copy()
tempArrivalMode = arrivalMode[10].copy()
uedatas = []
celldatas = []
while(len(tempPrach) > 0):
    maxIndex = tempPrach.index(max(tempPrach))
    for tau in folderName.keys():
        candidateIndex = findCandidateFolder(tempPrach[maxIndex], tempArrivalMode[maxIndex], folderName[tau])
#        print(resultSourceFolder + str(tau) + "/" + folderName[tau][candidateIndex])
        ue_filename = resultSourceFolder + str(tau) + "/" + folderName[tau][candidateIndex] + "/" + ueFile
        cell_filename = resultSourceFolder + str(tau) + "/" + folderName[tau][candidateIndex] + "/" + cellFile

        ### get ue data ###
        latency = [x['latency'] for x in collectDataUE(ue_filename).values()]
        uedata = {'tau':tau, 'latency':latency, 'prachIndex':prachIndex[tau][candidateIndex], 'simulationTime':simulationTime[tau][candidateIndex], 'arrivalMode':arrivalMode[tau][candidateIndex], 'arrival':arrival[tau][candidateIndex]}
        uedatas.append(uedata)
        ### get ue data ###

        ### get cell data ###
        nBeams, timing, preambleSCS, msg1FDM, ssbPerRAO, delta, raAttemptPeriod = collectDataCell(cell_filename)
        celldata = {'tau':tau,
                'prachIndex': prachIndex[tau][candidateIndex],
                'simulationTime':simulationTime[tau][candidateIndex],
                'arrivalMode':arrivalMode[tau][candidateIndex],
                'arrival':arrival[tau][candidateIndex],
                'nBeams':nBeams,
                'timing':timing,
                'preambleSCS':preambleSCS,
                'preambleLength':getPreambleLength(float(preambleSCS)),
                'msg1FDM':msg1FDM,
                'ssbPerRAO':ssbPerRAO,
                'delta':delta,
                'RA attempt period':raAttemptPeriod}
        celldatas.append(celldata)
        ### get cell data ###

    del tempPrach[maxIndex]
    del tempArrivalMode[maxIndex]
plotLantencyCDF(uedatas, resultSourceFolder)
plotCellMsg1FDM(celldatas, resultSourceFolder)
plotCellSSBPerRAO(celldatas, resultSourceFolder)
plotCellDelta(celldatas, resultSourceFolder)
plotCellTau(celldatas, resultSourceFolder)

print("DONE!")
del uedatas
del celldatas
del folderName
del prachIndex
del simulationTime
del arrivalMode
del arrival
