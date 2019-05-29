import os
import csv
import matplotlib.pyplot as plt
import numpy as np
import math
from plot_result import collectDataUE
from evaluateResult import collectCellMsg1FDM, getPreambleLength
from math import log

figureCount = 0

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
    print("Plotting Latency CDF")
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                fig.subplots_adjust(top=0.85)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Latency (ms)", fontsize=12)
                plt.ylabel("CDF",fontsize=12)
                plt.suptitle("UE Latency CDF", fontsize=14, fontweight="bold")
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), uedatas)
                    data = uedatas[candidateIndex]
                    latency = data['latency']
                    arrival = data['arrival']
                    subTitle = "prach-ConfigurationIndex: {0} Simulation Time: {1}\n".format(str(prach), str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    ax.set_title(subTitle)
                    
                    latency.insert(0, 0)
                    X = np.linspace(min(latency), max(latency), max(latency) - min(latency))
                    hist, bin_edges = np.histogram(latency, bins=max(latency) - min(latency), density=True)
                    hist = np.cumsum(hist)

                    plt.plot(X, hist, label=r"$\tau\ Threshold$="+str(tau))
                    ax.legend(loc="lower right")
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
    print("Plotting Msg1FDM")
    global figureCount
    newYTick = [fdm*celldatas[0]['preambleLength']*float(celldatas[0]['preambleSCS'])/1000 for fdm in [1, 2, 4, 8]]
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                fig.subplots_adjust(top=0.85)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=12)
                plt.ylabel("Preamble Occupied Bandwidth (MHz)", fontsize=12)
                plt.suptitle(r"RA Used Bandwidth For Each $\tau$ Threshold", fontsize=14, fontweight="bold")
                plt.yticks(newYTick)
                i = 0
                attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-*']
                maxTiming = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "prach-ConfigurationIndex: {0}".format(str(prach)) \
                            + " Simulation Time: {0}\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    ax.set_title(subTitle)
                    
                    preambleBW = [fdm*data['preambleLength']*float(data['preambleSCS'])/1000 for fdm in data['msg1FDM']]
                    maxTiming = max([maxTiming, max(data['timing'])])
                    ax.plot(data['timing'], preambleBW, attr[i], label=r'$\tau\ Threshold$='+str(tau))
                    i = i + 1
                filenameFig = "RA_Used_BW_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                ax.legend(loc="upper left")
                ax.set_xlim(0, maxTiming)
                ax.set_ylim(0, math.ceil(max(newYTick) / 10) * 10)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()
                    
def plotCellSSBPerRAO(celldatas, saveFolderName=""):
    print("Plotting SSB per RAO")
    global figureCount
    newYTick = [0.125, 0.25, 0.5, 1, 2, 4, 8, 16]
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                fig.subplots_adjust(top=0.85)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=12)
                plt.ylabel(r"SSB Per RAO $S_{RAO}$", fontsize=12)
                plt.suptitle(r"Number of SSB Per RAO $S_{RAO}$ For Each $\tau$ Threshold", fontsize=14, fontweight="bold")
                plt.yticks(newYTick)
                i = 0
                attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-*']
                maxTiming = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "prach-ConfigurationIndex: {0}".format(str(prach)) \
                            + " Simulation Time: {0}\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    ax.set_title(subTitle)
                    
                    maxTiming = max([maxTiming, max(data['timing'])])
                    ax.plot(data['timing'], data['ssbPerRAO'], attr[i], label=r'$\tau\ Threshold$='+str(tau))
                    i = i + 1
                filenameFig = "S_RAO_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                ax.legend(loc="upper left")
                ax.set_xlim(0, maxTiming)
                ax.set_ylim(newYTick[0], newYTick[-1])
                ax.set_yscale('log', basey=2)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()

def plotCellDelta(celldatas, saveFolderName=""):
    print("Plotting Channel Capacity")
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                fig.subplots_adjust(top=0.85)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=12)
                plt.ylabel(r"Channel Capacity $\delta$", fontsize=12)
                plt.suptitle(r"Channel Capacity $\delta$ For Each $\tau$ Threshold", fontsize=14, fontweight="bold")
                i = 0
                attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-*']
                maxTiming = 0
                maxDelta = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "prach-ConfigurationIndex: {0}".format(str(prach)) \
                            + " Simulation Time: {0}\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    ax.set_title(subTitle)
                    
                    maxTiming = max([maxTiming, max(data['timing'])])
                    maxDelta = max([maxDelta, max(data['delta'])])
                    ax.plot(data['timing'], data['delta'], attr[i], label=r'$\tau\ Threshold$='+str(tau))
                    i = i + 1
                filenameFig = "Delta_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                ax.legend(loc="upper left")
                ax.set_xlim(0, maxTiming)
                exponential = math.floor(log(maxDelta, 10))
                coef = maxDelta / pow(10, exponential)
                maxDelta = (coef + 1) * pow(10, exponential)
                ax.set_ylim(0, maxDelta)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()

def plotCellTau(celldatas, saveFolderName=""):
    print("Plotting Tau")
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.set_size_inches(9.375, 7.3)
                fig.subplots_adjust(top=0.85)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Subframe Index", fontsize=12)
                plt.ylabel(r"RA Attempt Period $\tau$", fontsize=12)
                plt.suptitle(r"RA Attempt Period $\tau$ For Each $\tau$ Threshold", fontsize=14, fontweight="bold")
                i = 0
                attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-*']
                maxTiming = 0
                maxTau = 0
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findCandidate(tau, str(prach), arrivalMode, str(simulation), celldatas)
                    data = celldatas[candidateIndex]
                    arrival = data['arrival']
                    subTitle = "prach-ConfigurationIndex: {0}".format(str(prach)) \
                            + " Simulation Time: {0}\n".format(str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Total UE: {0}".format(arrival)
                    ax.set_title(subTitle)
                    
                    maxTiming = max([maxTiming, max(data['timing'])])
                    maxTau = max([maxTau, max(data['RA attempt period'])])
                    ax.plot(data['timing'], data['RA attempt period'], attr[i], label=r'$\tau\ Threshold$='+str(tau))
                    i = i + 1
                filenameFig = "RA_attempt_periodprach-{0}_simu-{1}_{2}_arrival-{3}".format(prach,
                        simulation,
                        arrivalMode,
                        arrival)
                ax.legend(loc="upper left")
                ax.set_xlim(0, maxTiming)
                #exponential = math.floor(log(maxTau, 10))
                #coef = maxTau / pow(10, exponential)
                #maxTau = (coef + 1) * pow(10, exponential)
                #ax.set_ylim(0, maxTau)
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                    plt.close()

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
