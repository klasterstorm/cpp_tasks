from matplotlib import pyplot

f = open("Task1_output.txt", "r") 


allData = []
namesData = []
valueData = []


for row in f:
    row = row.replace("\n", "")
    rowArray = row.split(" ")

    allData.append(rowArray)

    name = rowArray[0]

    if name not in namesData:
        namesData.append(name)
        valueData.append([])

for (i, namei) in enumerate(namesData):

    for data in allData:
        currentName = data[0]
        val1 = int(data[1])
        val2 = int(data[2])

        if currentName == namei:
            valueData[i].append([val1, val2])


for (i, dataName) in enumerate(namesData):
    val1 = []
    val2 = []

    for valData in valueData[i]:
        val1.append(valData[0])
        val2.append(valData[1])

    pyplot.plot(val1, val2, label = dataName)

pyplot.legend(loc="upper left")
pyplot.show()


