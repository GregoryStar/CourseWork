import random
name = input("Enter a file name: ")
f = open(name, 'w')
for i in range (0, 1000):
    x = random.randint(-1000, 1000)
    toWrite = str(i + 1) + ", " + str(x) + "\n"
    f.write(toWrite)
f.close()
