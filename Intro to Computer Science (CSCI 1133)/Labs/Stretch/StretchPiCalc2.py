import math
tol = float(input("Input a tolerance: "))
pi = 0
atmpO = (6/math.sqrt(3))
atmpN = 100
c = 0
while abs(atmpO - atmpN)>tol:
    temp = atmpN
    atmpN = atmpO + (-1) * (c % 2) * ((6/math.sqrt(3)) * (1/((3**(c+1))*(3+(2*c)))))
    atmpO = temp
    c += 1
    pi = atmpN
print(pi)

    
