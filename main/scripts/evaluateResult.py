#/usr/bin/python3
import os
import csv
import matplotlib as plt
import numpy as np
from plot_result import collectDataUE

ueFile = 'UE.csv'
cellFile = 'Cell.csv'
resultSourceFolder = "./candidateResult/"

folderName = [name for name in os.listdir(resultSourceFolder)]

temp = [name.split("prach-")[1] for name in folderName]
temp = [name.split("_")[0] for name in temp]

avgs = []

while(len(temp) > 0):
    maxIndex = temp.index(max(temp))
    filename = resultSourceFolder + folderName[maxIndex] + "/" + ueFile
    latencies = collectDataUE(filename)
    avgs.append(np.mean(list(latencies.values())))
    #print(temp[maxIndex])
    #print(folderName[maxIndex])
    #print(filename)
    #print(len(latencies))
    del temp[maxIndex]
    del folderName[maxIndex]
    del latencies

print(avgs)
del avgs
