c = 100
tempsEqual = False
while not tempsEqual:
    tempInF = int((((9/5) * c) + 32))
    if tempInF == c:
        tempsEqual = True
        c += 1
    c -= 1
print(c)
