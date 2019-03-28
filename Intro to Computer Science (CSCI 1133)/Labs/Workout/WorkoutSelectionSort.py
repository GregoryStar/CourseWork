listofshit = []
entering = True
while entering:
    n = input("Enter an integer. Enter 'stop' to stop.")
    if n == "stop":
        entering = False
    else:
        n = int(n)
        listofshit.append(n)
print(listofshit)
#Here comes the sorting
for x in range(0, len(listofshit)):
    z = min(listofshit[x:])
    c = 0
    pos = 0
    while c < len(listofshit):
        if listofshit[c] == z:
            pos = c
        c+=1
    y = listofshit[x]
    listofshit[x] = z
    listofshit[pos] = y

print(listofshit)
