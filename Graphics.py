from matplotlib import pyplot

f = open("outputFile.txt", "r")

a = []
b = []

isNew = False

for x in f:
    if x == "------\n" and not isNew:
        isNew = True

    if x != "" and x != "------\n":
        if isNew:
            a.append(int(x))
        else:
            b.append(int(x))



arrOfX = []

maxNumberOfIterations = 10000000
initialBlockSize = 1000
blockStride = 5

blockSize = initialBlockSize

for i in range(0, 6):
    blockSize *= blockStride
    arrOfX.append(blockSize)
    print(blockSize)



pyplot.plot(a, arrOfX, 'b', label = "EvenOdd")
pyplot.plot(b, arrOfX, 'r', label = "Random")
pyplot.ylabel('b - evenOdd, r - random')
pyplot.legend(loc="upper left")
pyplot.show()


