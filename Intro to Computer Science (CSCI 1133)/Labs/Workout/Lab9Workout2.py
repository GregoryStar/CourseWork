f = open("2.5_day.csv", "r")
listOfLines = []
for line in f:
    listOfLines += [line]
listOfLines = listOfLines[0:]
print(listOfLines)
unsortedList = []
for line in listOfLines:
    listOfTerms = []
    while line.find(",") != -1:
        listOfTerms += [line[:line.find(",")]]
        line = line[line.find(",") + 1:]
    listOfTerms += [line]
    location = listOfTerms[14]
    location = location[:len(location) - 1]
    unsortedList.append([listOfTerms[4], location])
sortedList = sorted(unsortedList, key=lambda term: term[0])
sortedList = sortedList[:len(sortedList) - 1]
print(unsortedList)
for term in sortedList:
    print("Magnitude: ", term[0], ", Location: ", term[1])

f.close()
