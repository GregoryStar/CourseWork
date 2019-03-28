import random
a = [0,0,0,0,0,0,0,0,0,0,0]
for c in range(1, 10000):
    r1 = random.randint(1, 6)
    r2 = random.randint(1, 6)
    a[r1+r2-2] += 1
print(a)
