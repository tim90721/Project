#/usr/bin/python3
import os
import csv
import matplotlib.pyplot as plt
import numpy as np
from plot_result import collectDataUE
import math

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

def getPreambleLength(preambleSCS):
    if preambleSCS == 1.25 or preambleSCS == 5:
        return 839
    else:
        return 139

def collectCellMsg1FDM(filename):
    timing = []
    msg1FDM = []
    with open(filename, newline='') as csvfile:
        rows = csv.DictReader(csvfile)
        #next(rows)
        for row in rows:
            preambleSCS = row['Preamble SCS']
            timing.append(int(row['Current Frame']) * 10 + int(row['Current Subframe']))
            msg1FDM.append(int(row['msg1-FDM']))
    return preambleSCS, timing, msg1FDM

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

def plotLantencyCDF(uedata, saveFolderName=""):
    global figureCount
    fig = plt.figure(figureCount)
    figureCount = figureCount + 1
    fig.subplots_adjust(top=0.85)
    ax = plt.subplot(1, 1, 1)

    plt.xlabel("Latency (ms)")
    plt.ylabel("CDF")
    plt.suptitle("UE Latency CDF", fontsize=14, fontweight="bold")

    for data in uedata:
        latency = data['latency']
        prachIndex = data['prachIndex']
        simulationTime = data['simulationTime']
        arrivalMode = data['arrivalMode']
        arrival = data['arrival']
        subTitle = "Simulation Time: {0}\n".format(str(int(simulationTime))) \
                + "Arrival Mode: {0}, ".format(arrivalMode)
        if arrivalMode == "uniform":
            subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
        else:
            subTitle = subTitle + "Totle UE: {0}".format(arrival)
        filenameFig = "CDF_simu-{0}_{1}_arrival-{2}".format(simulationTime,
                arrivalMode,
                arrival)
        ax.set_title(subTitle)

        latency.insert(0, 0)
        X = np.linspace(min(latency), max(latency), max(latency) - min(latency))
        hist, bin_edges = np.histogram(latency, bins=max(latency) - min(latency), density=True)
        hist = np.cumsum(hist)

        plt.plot(X, hist, label="Prach Configuration Index="+prachIndex)
        ax.legend(loc="lower right")
    plt.axis([0, max(latency), 0, 1.1])
    plt.grid(True)
    if saveFolderName:
        plt.savefig(saveFolderName + filenameFig)
    del X
    del hist
    del bin_edges

def plotEachLantencyCDF(uedata, saveFolderName=""):
    global figureCount
    for data in uedata:
        fig = plt.figure(figureCount)
        figureCount = figureCount + 1
        fig.subplots_adjust(top=0.85)
        ax = plt.subplot(1, 1, 1)

        plt.xlabel("Latency (ms)")
        plt.ylabel("CDF")
        plt.suptitle("UE Latency CDF", fontsize=14, fontweight="bold")
        latency = data['latency']
        prachIndex = data['prachIndex']
        simulationTime = data['simulationTime']
        arrivalMode = data['arrivalMode']
        arrival = data['arrival']
        subTitle = "Prach Configuration Index: {0}, ".format(prachIndex) \
                + "Simulation Time: {0}\n".format(str(int(simulationTime))) \
                + "Arrival Mode: {0}, ".format(arrivalMode)
        if arrivalMode == "uniform":
            subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
        else:
            subTitle = subTitle + "Totle UE: {0}".format(arrival)
        filenameFig = "CDF_prach-{0}_simu-{1}_{2}_arrival-{3}".format(prachIndex,
                simulationTime,
                arrivalMode,
                arrival)
        ax.set_title(subTitle)

        latency.insert(0, 0)
        X = np.linspace(min(latency), max(latency), max(latency) - min(latency))
        hist, bin_edges = np.histogram(latency, bins=max(latency) - min(latency), density=True)
        hist = np.cumsum(hist)

        plt.plot(X, hist, 'b-')
        plt.axis([0, max(latency), 0, 1.1])
        plt.grid(True)
        if saveFolderName:
            plt.savefig(saveFolderName + filenameFig)
    del X
    del hist
    del bin_edges

def plotCellMsg1FDM(celldatas, folderName=""):
    global figureCount
    fig = plt.figure(figureCount)
    fig.set_size_inches(9.375, 7.3)
    simulationTime = celldatas[0]['simulationTime']
    arrivalMode = celldatas[0]['arrivalMode']
    arrival = celldatas[0]['arrival']
    maxTiming = max([max(t['timing']) for t in celldatas])
    ax = plt.subplot(1, 1, 1)
    figureCount = figureCount + 1
    attr = ['b-s', 'r-o', 'm-D', 'c-^', 'g-*']
    i = 0
    for data in celldatas:
        preambleBW = [fdm*data['preambleLength']*float(data['preambleSCS'])/1000 for fdm in data['msg1FDM']]
        ax.plot(data['timing'], preambleBW, attr[i], label='prach-ConfigurationIndex='+data['prachIndex'])
        i = i + 1
    newYTick = [fdm*celldatas[0]['preambleLength']*float(celldatas[0]['preambleSCS'])/1000 for fdm in [1, 2, 4, 8]]

    plt.yticks(newYTick)
    ax.legend(loc='upper left')
    ax.set_xlim(0, maxTiming)
    ax.set_ylim(0, math.ceil(max(newYTick) / 10) * 10)
    ax.grid(True)
    plt.xlabel("Subframe Index", fontsize=14)
    plt.ylabel("Preamble Occupied Bandwidth (MHz)",fontsize=14)
    plt.suptitle("RA Used Bandwidth", fontsize=18, fontweight="bold")
    title = "Simulation Time: {0}\nArrival Mode:{1}".format(simulationTime, arrivalMode)
    if arrivalMode == "uniform":
        title = title + ", Arrival Rate:{0}".format(arrival)
    else:
        title = title + ", Total UE:{0}".format(arrival)
    filename = "msg1FDM_simu-{0}_{1}_arrival-{2}.png".format(simulationTime,
            arrivalMode,
            arrival)
    plt.title(title, fontsize=16)
    plt.savefig(folderName + filename)

ueFile = 'UE.csv'
cellFile = 'Cell.csv'
resultSourceFolder = "./candidateResult/"
savefigureNameUniform = "result_uniform.png"
savefigurenameBeta = "result_beta.png"
folderNameUniform = "uniform/"
folderNameBeta = "beta/"

if not os.path.exists(resultSourceFolder + folderNameUniform):
    os.makedirs(resultSourceFolder + folderNameUniform)
if not os.path.exists(resultSourceFolder + folderNameBeta):
    os.makedirs(resultSourceFolder + folderNameBeta)

folderName = [name for name in os.listdir(resultSourceFolder)]
folderName = [name for name in folderName if "png" not in name]
folderName.remove('beta')
folderName.remove('uniform')

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
#    print(prachIndex[i])
#    print(simulationTime[i])
#    print(arrivalMode[i])
#    print(arrival[i])
############ get parameters ############

avgs_uniform = {}
avgs_beta = {}
ue_uniform = []
ue_beta = []
cell_uniform = []
cell_beta = []

while(len(prachIndex) > 0):
    maxIndex = prachIndex.index(max(prachIndex))
    #### get ue data ####
    filename = resultSourceFolder + folderName[maxIndex] + "/" + ueFile
    latency = [x['latency'] for x in collectDataUE(filename).values()]
    ue_data = {'latency':latency, 'prachIndex':prachIndex[maxIndex], 'simulationTime':simulationTime[maxIndex], 'arrivalMode':arrivalMode[maxIndex], 'arrival':arrival[maxIndex]}
    #### get ue data ####
    #### get cell data ####
    filename = resultSourceFolder + folderName[maxIndex] + "/" + cellFile
    preambleSCS, timing, msg1FDM = collectCellMsg1FDM(filename)
    cell_data = {'prachIndex':prachIndex[maxIndex], 'preambleSCS':preambleSCS, 'preambleLength':getPreambleLength(float(preambleSCS)), 'timing':timing, 'msg1FDM':msg1FDM, 'simulationTime':simulationTime[maxIndex], 'arrivalMode': arrivalMode[maxIndex], 'arrival':arrival[maxIndex]}
    #### get cell data ####
    if arrivalMode[maxIndex] == "uniform":
        avgs_uniform[getSubframePeriod(int(prachIndex[maxIndex]))] = np.mean(latency)
        cell_uniform.append(cell_data)
        ue_uniform.append(ue_data)
    else:
        avgs_beta[getSubframePeriod(int(prachIndex[maxIndex]))] = np.mean(latency)
        cell_beta.append(cell_data)
        ue_beta.append(ue_data)

#    plotLantencyCDF(latency, prachIndex[maxIndex], simulationTime[maxIndex], arrivalMode[maxIndex], arrival[maxIndex], resultSourceFolder)
    del prachIndex[maxIndex]
    del simulationTime[maxIndex]
    del arrivalMode[maxIndex]
    del arrival[maxIndex]
    del folderName[maxIndex]

print(avgs_uniform)
plotLantencyCDF(ue_uniform, resultSourceFolder + folderNameUniform)
plotEachLantencyCDF(ue_uniform, resultSourceFolder + folderNameUniform)
plotAverageResult(avgs_uniform, resultSourceFolder + folderNameUniform + savefigureNameUniform)
plotCellMsg1FDM(cell_uniform, resultSourceFolder + folderNameUniform)

plotLantencyCDF(ue_beta, resultSourceFolder + folderNameBeta)
plotEachLantencyCDF(ue_beta, resultSourceFolder + folderNameBeta)
plotAverageResult(avgs_beta, resultSourceFolder + folderNameBeta+ savefigurenameBeta)
plotCellMsg1FDM(cell_beta, resultSourceFolder + folderNameBeta)
#plt.show()
del avgs_uniform
del avgs_beta
del cell_uniform
del cell_beta
del ue_uniform
del ue_beta
