amount = eval(input("Input a loan ammount: "))
ar = eval(input("Input an interest rate: "))
r = ar/12
duration = eval(input("Enter the duration in months of the loan: "))
payment = (r*amount)/((1 - (1+r)**(-duration)))
print("The payment required to pay off the loan is: ", payment)
