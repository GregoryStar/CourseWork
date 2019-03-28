f = open("2.5_day.csv", "r")
listOfLines = []
for line in f:
    listOfLines += [line]
line1 = listOfLines[0]
listOfTerms = []
while line1.find(",") != -1:
    listOfTerms += [line1[:line1.find(",")]]
    line1 = line1[line1.find(",") + 1:]
listOfTerms += [line1]
i = 0
for term in listOfTerms:
    print(i, term)
    i += 1



f.close()
