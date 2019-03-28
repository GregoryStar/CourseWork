import random
import math
sampSize = 100000
sampInCircle = 0
c = 0
while c < sampSize:
    y = random.random()*2 - 1
    x = random.random()*2 - 1
    if math.sqrt((y**2 + x**2)) <= 1:
        sampInCircle += 1
    c += 1
pi = (sampInCircle/sampSize)*4
print(pi)
