import math

with open("data.txt", "r") as data:
    
    filelines = data.readlines()
    timestamp = []
    value = []

    for l in filelines:
        datapoint = l.split(" ")
        timestamp.append(datapoint[0])
        value.append(datapoint[1].replace("\n", ""))

    print(timestamp)
    print(value)