import operator
fileName = input("Enter a file name: ")
f = open(fileName, "r")
listReserved = ["False", "class", "finally", "is", "return", "None", "continue", "for", "lambda", "try", "True", "def", "from", "nonlocal",
                "while", "and", "del", "global", "not", "with", "as", "elif", "if", "or", "yield", "assert", "else", "import", "pass",
                "break", "except", "in", "raise"]
occurances = [0] * len(listReserved)
dictReserved = dict(zip(listReserved, occurances))
for line in f:
    for keyWord in listReserved:
        if keyWord in line:
            dictReserved[keyWord] += 1
sortedScores = sorted(dictReserved.items(), key=operator.itemgetter(0))

for pair in sortedScores:
    if pair[1] != 0:
        print(pair[0],":",pair[1])
f.close()
