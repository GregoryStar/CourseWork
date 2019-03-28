f = open("cDc-0200.txt", "r")
longString = ""
for line in f:
    for ch in line:
        if ch.isalpha():
            longString += ch
longString = longString.lower()
listByCh = [0]*26
i = 0
for ch in "abcdefghijklmnopqrstuvwxyz":
    for ch2 in longString:
        if ch == ch2:
            listByCh[i] += 1
    i+=1
print(listByCh)

f.close()
