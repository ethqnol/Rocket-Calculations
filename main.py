import math
import time


iterable = 0
flag = False  

def getData():
    with open("data.txt", "r") as data:
        
        filelines = data.readlines()
        timestamp = []
        value = []

        for l in filelines:
            datapoint = l.split(" ")
            timestamp.append(datapoint[0])
            value.append(datapoint[1].replace("\n", ""))
    
    ListOfStuff = [timestamp, value]
        
    return ListOfStuff

def calculateVelocity(current, initial, timedelta):
    velocity = current - initial + 9.8 * timedelta * timedelta
    return velocity




def main():
    gate = True
    startVelCalc = False
    while True:
        data = getData()
        timestamp = data[0]
        value = data[1]
        latestData = int(value[len(value) - 1])
        recentData = int(value[len(value) - 6])
        
        if gate and latestData < recentData:
            gate = False
            startVelCalc = True

        if startVelCalc == True:
            deltaTime = int(timestamp[len(value) - 1]) - int(value[len(value) - 6])
            calculateVelocity(latestData, recentData, deltaTime)

        
main()


    
