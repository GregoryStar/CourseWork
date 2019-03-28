name = input("Enter a file name: ")
f = open(name, 'r')
currentMin = 0
currentMax = 0
for line in f:
    x = f.read()
    i = x.find(",")
    x = x[i+1:]
    i = x.find("\n")
    x = x[:i]
    x = int(x)
    if x > currentMax:
        currentMax = x
    elif x < currentMin:
        currentMin = x

print(currentMin, " ", currentMax)
f.close()
