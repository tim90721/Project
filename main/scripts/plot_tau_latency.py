import os
import csv
import matplotlib.pyplot as plt
import numpy as np
import math
from plot_result import collectDataUE, collectDataCell
from evaluateResult import collectCellMsg1FDM

figureCount = 0

def findCandidate(targetPrach, targetArrival, folderName):
    candidateIndex = [index for index in range(len(folderName)) if "prach-"+targetPrach in folderName[index]]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if targetArrival in folderName[candidateIndex[index]]]
    #print(folderName)
    #print(candidateIndex)
    #print("target prach: ", targetPrach)
    #print("target arrival: ", targetArrival)
    #print("candidate folder: ", [folderName[candidateIndex[index]] for index in range(len(candidateIndex))])
    return candidateIndex[0]

def findUECandidate(targetTau, targetPrach, targetArrival, targetSimulation, datas):
    candidateIndex = [index for index in range(len(datas)) if datas[index]['tau'] == targetTau]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if datas[candidateIndex[index]]['prachIndex'] == targetPrach]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if datas[candidateIndex[index]]['arrivalMode'] == targetArrival]
    candidateIndex = [candidateIndex[index] for index in range(len(candidateIndex)) if datas[candidateIndex[index]]['simulationTime'] == targetSimulation]
    #print(candidateIndex)
    return candidateIndex[0]

def plotLantencyCDF(uedatas, saveFolderName=""):
    global figureCount
    for arrivalMode in ['uniform', 'beta']:
        for prach in [16, 19, 22, 25, 27]:
            for simulation in [1]:
                fig = plt.figure(figureCount)
                figureCount = figureCount + 1
                fig.subplots_adjust(top=0.85)
                ax = plt.subplot(1, 1, 1)

                plt.xlabel("Latency (ms)")
                plt.ylabel("CDF")
                plt.suptitle("UE Latency CDF", fontsize=14, fontweight="bold")
                for tau in [10, 20, 40, 80, 160]:
                    candidateIndex = findUECandidate(tau, str(prach), arrivalMode, str(simulation), uedatas)
                    data = uedatas[candidateIndex]
                    latency = data['latency']
                    arrival = data['arrival']
                    subTitle = "prach-ConfigurationIndex: {0} Simulation Time: {1}\n".format(str(prach), str(simulation)) \
                            + "Arrival Mode: {0}, ".format(arrivalMode)
                    if arrivalMode == "uniform":
                        subTitle = subTitle + "Arrival Rate: {0}".format(arrival)
                    else:
                        subTitle = subTitle + "Totle UE: {0}".format(arrival)
                    filenameFig = "CDF_tau-{0}_prach-{1}_simu-{2}_{3}_arrival-{4}".format(tau,
                            prach,
                            simulation,
                            arrivalMode,
                            arrival)
                    ax.set_title(subTitle)
                    
                    latency.insert(0, 0)
                    X = np.linspace(min(latency), max(latency), max(latency) - min(latency))
                    hist, bin_edges = np.histogram(latency, bins=max(latency) - min(latency), density=True)
                    hist = np.cumsum(hist)

                    plt.plot(X, hist, label=r"$\tau Threshold$="+str(tau))
                    ax.legend(loc="lower right")
                plt.axis([0, max(latency), 0, 1.1])
                plt.grid(True)
                if saveFolderName:
                    plt.savefig(saveFolderName + arrivalMode + "/"  + filenameFig)
                del X
                del hist
                del bin_edges
                    
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
while(len(tempPrach) > 0):
    maxIndex = tempPrach.index(max(tempPrach))
    for tau in folderName.keys():
        candidateIndex = findCandidate(tempPrach[maxIndex], tempArrivalMode[maxIndex], folderName[tau])
#        print(resultSourceFolder + str(tau) + "/" + folderName[tau][candidateIndex])
        ue_filename = resultSourceFolder + str(tau) + "/" + folderName[tau][candidateIndex] + "/" + ueFile
        cell_filename = resultSourceFolder + str(tau) + "/" + folderName[tau][candidateIndex] + "/" + cellFile

        ### get ue data ###
        latency = [x['latency'] for x in collectDataUE(ue_filename).values()]
        uedata = {'tau':tau, 'latency':latency, 'prachIndex':prachIndex[tau][candidateIndex], 'simulationTime':simulationTime[tau][candidateIndex], 'arrivalMode':arrivalMode[tau][candidateIndex], 'arrival':arrival[tau][candidateIndex]}
        uedatas.append(uedata)
        ### get ue data ###

        ### get cell data ###
        ### get cell data ###

        #print(uedata)
    del tempPrach[maxIndex]
    del tempArrivalMode[maxIndex]
plotLantencyCDF(uedatas, resultSourceFolder)

print("DONE!")
