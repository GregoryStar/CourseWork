value = eval(input("Enter a 4 digit integer: "))
thous = value // 1000
hund = (value // 100) % 10
tens = (value // 10) % 10
ones = value % 10
print(thous)
print(hund)
print(tens)
print(ones)
