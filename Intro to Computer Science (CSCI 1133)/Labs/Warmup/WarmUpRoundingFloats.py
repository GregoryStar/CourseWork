x = float(input("Enter a number: "))
if x > 0:
    xi = int((x + 0.5))
    print(xi)
elif x < 0:
    xi = int((x - 0.5))
    print(xi)
else:
    print("0")
