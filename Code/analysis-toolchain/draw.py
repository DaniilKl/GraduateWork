#!/usr/bin/env python3

import os
import glob
import json
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import sys


def concatinate_data(pattern):
    ConcatinatedData = {}

    for FilePath in glob.glob(pattern):
        try:
            with open(FilePath, 'r', encoding='utf-8') as File:
                Content = json.load(File)
            ConcatinatedData[os.path.basename(FilePath)] = Content
        except json.JSONDecodeError as e:
            print(f"Error decoding JSON in file {FilePath}: {e}")
        except Exception as e:
            print(f"Error processing file {FilePath}: {e}")

    return ConcatinatedData


def extract_xy(data, x, y):
    X = []
    Y = []

    FilesNames = list(data)
    DataCount = len(FilesNames)

    for i in range(0, DataCount):
        YNames = list(data[FilesNames[i]][y])
        YNamesCount = len(YNames)
        YSum = 0

        for j in range(0, YNamesCount):
            YSum = YSum + data[FilesNames[i]][y][YNames[j]]

        Y.append(YSum)
        X.append(data[FilesNames[i]][x])

    Size=len(X)
    for i in range(Size):
        for j in range(0, Size - i - 1):
            if X[j] > X[j + 1]:  # Swap if the current element is bigger than the next
                X[j], X[j + 1] = X[j + 1], X[j]
                Y[j], Y[j + 1] = Y[j + 1], Y[j]

#    coefficients = np.polyfit(X, Y, deg=12)
#    polynomial = np.poly1d(coefficients)
#    X = np.linspace(min(X), max(X), 100)
#    Y = polynomial(X)

    return X, Y


def draw_loadfactor_misses(algorithm_name, x, y):
    plt.plot(x, y, label=f"{algorithm_name}")
    plt.xlabel("Obciążenie")
    plt.ylabel("Ilość niespełnionych deadlinów")
    plt.legend()
    plt.grid()

    return plt


def draw_loadfactor_catches(algorithm_name, x, y):
    plt.plot(x, y, label=f"{algorithm_name}")
    plt.xlabel("Obciążenie")
    plt.ylabel("Ilość spełnionych deadlinów")
    plt.legend()
    plt.grid()

    return plt


def draw_avaragetime_misses(algorithm_name, x, y):
    plt.plot(x, y, label=f"{algorithm_name}")
    plt.xlabel("Średni czas wykonywania procesu [SysTick]")
    plt.ylabel("Ilość niespełnionych deadlinów")
    plt.legend()
    plt.grid()

    return plt


def draw_avaragetime_catches(algorithm_name, x, y):
    plt.plot(x, y, label=f"{algorithm_name}")
    plt.xlabel("Średni czas wykonywania procesu [SysTick]")
    plt.ylabel("Ilość spełnionych deadlinów")
    plt.legend()
    plt.grid()

    return plt

def SmoothOutData(x, y):
    print(f"Data before smoothing: {y}")
    sma = np.convolve(y, np.ones(5) / 5, mode='valid')
    x = x[:-4]
    print(f"Data after smoothing: {sma}")
    return x, sma


def main():
    if len(sys.argv) != 4:
        print("Usage: ./analyze.py <use_smoothing> <directories_pattern> <files_pattern>")
        sys.exit(1)

    UseSmoothing = sys.argv[1]
    DirectoriesPattern = sys.argv[2]
    FilesPattern = sys.argv[3]

    for DirectoryPath in glob.glob(DirectoriesPattern):
        AlgorithmName = DirectoryPath.split("-")[0]
        PathPattern = os.path.join(DirectoryPath, FilesPattern)
        ConcatinatedDataPath = os.path.join(DirectoryPath, f"{AlgorithmName}-concatinated-data.json")

        # Initialize a dictionary to store the contents
        ConcatinatedData = concatinate_data(PathPattern)

        with open(ConcatinatedDataPath, 'w') as json_file:
            json.dump(ConcatinatedData, json_file, indent=4)

        XLoadfactorMissed, YLoadFactorMissed = extract_xy(ConcatinatedData, "LoadFactor", "MissDeadline")

        if UseSmoothing == 'true':
            XLoadfactorMissed, YLoadFactorMissed = SmoothOutData(XLoadfactorMissed, YLoadFactorMissed)

        PlotLoadfactorMissed = draw_loadfactor_misses(AlgorithmName, XLoadfactorMissed, YLoadFactorMissed)
    
    PlotLoadfactorMissed.savefig(os.path.join("./", "loadfactor-misses.png"), dpi=300, bbox_inches='tight')
    PlotLoadfactorMissed.show()
    plt.cla()


    for DirectoryPath in glob.glob(DirectoriesPattern):
        AlgorithmName = DirectoryPath.split("-")[0]
        PathPattern = os.path.join(DirectoryPath, FilesPattern)
        ConcatinatedDataPath = os.path.join(DirectoryPath, f"{AlgorithmName}-concatinated-data.json")

        # Initialize a dictionary to store the contents
        ConcatinatedData = concatinate_data(PathPattern)

        with open(ConcatinatedDataPath, 'w') as json_file:
            json.dump(ConcatinatedData, json_file, indent=4)

        XLoadfactorCatched, YLoadFactorCatched = extract_xy(ConcatinatedData, "LoadFactor", "MetDeadline")

        if UseSmoothing == 'true':
            XLoadfactorCatched, YLoadFactorCatched = SmoothOutData(XLoadfactorCatched, YLoadFactorCatched)

        PlotLoadfactorCatched = draw_loadfactor_catches(AlgorithmName, XLoadfactorCatched, YLoadFactorCatched)
    
    PlotLoadfactorCatched.savefig(os.path.join("./", "loadfactor-catches.png"), dpi=300, bbox_inches='tight')
    PlotLoadfactorCatched.show()
    plt.cla()


    for DirectoryPath in glob.glob(DirectoriesPattern):
        AlgorithmName = DirectoryPath.split("-")[0]
        PathPattern = os.path.join(DirectoryPath, FilesPattern)
        ConcatinatedDataPath = os.path.join(DirectoryPath, f"{AlgorithmName}-concatinated-data.json")

        # Initialize a dictionary to store the contents
        ConcatinatedData = concatinate_data(PathPattern)

        with open(ConcatinatedDataPath, 'w') as json_file:
            json.dump(ConcatinatedData, json_file, indent=4)

        XAvaragetimeMissed, YAvaragetimeMissed = extract_xy(ConcatinatedData, "MeanTaskExecutionTime", "MissDeadline")

        if UseSmoothing == 'true':
            XAvaragetimeMissed, YAvaragetimeMissed = SmoothOutData(XAvaragetimeMissed, YAvaragetimeMissed)

        PlotAvaragetimeMissed = draw_avaragetime_misses(AlgorithmName, XAvaragetimeMissed, YAvaragetimeMissed)

    PlotAvaragetimeMissed.savefig(os.path.join("./", "avaragetime-misses.png"), dpi=300, bbox_inches='tight')
    plt.cla()


    for DirectoryPath in glob.glob(DirectoriesPattern):
        AlgorithmName = DirectoryPath.split("-")[0]
        PathPattern = os.path.join(DirectoryPath, FilesPattern)
        ConcatinatedDataPath = os.path.join(DirectoryPath, f"{AlgorithmName}-concatinated-data.json")

        # Initialize a dictionary to store the contents
        ConcatinatedData = concatinate_data(PathPattern)

        with open(ConcatinatedDataPath, 'w') as json_file:
            json.dump(ConcatinatedData, json_file, indent=4)

        XAvaragetimeCatched, YAvaragetimeCatched = extract_xy(ConcatinatedData, "MeanTaskExecutionTime", "MetDeadline")

        if UseSmoothing == 'true':
            XAvaragetimeCatched, YAvaragetimeCatched = SmoothOutData(XAvaragetimeCatched, YAvaragetimeCatched)

        PlotAvaragetimeCatched = draw_avaragetime_catches(AlgorithmName, XAvaragetimeCatched, YAvaragetimeCatched)

    PlotAvaragetimeCatched.savefig(os.path.join("./", "avaragetime-catches.png"), dpi=300, bbox_inches='tight')
    plt.cla()


if __name__ == "__main__":
    main()

