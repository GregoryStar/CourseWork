def rootN(n, root):
    x1 = 0
    x2 = n
    while abs(x1 - x2) > 0.00001:
        x1 = x2
        x2 = x1 - (x1**root - n)/(root * x1 ** (root - 1))
    return x2

cont = True
while cont:
    n = float(input("Enter value: "))
    root = float(input("Enter root: "))
    sqrt = rootN(n, root)
    print("The root is: ", sqrt)
    ans = input("Continue? (y/n): ")
    if not(ans == 'y'):
        cont = False
    print()
