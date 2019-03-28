print("This program calculates wind chill")
t = eval(input("Enter a temperature in Fahrenheit: "))
v = eval(input("Enter a wind velocity: "))
windchill = 35.74 + 0.6215 * t - 35.75 * v**0.16 + 0.4275 * t * v ** 0.16
print("The wind chill is: ",windchill)
