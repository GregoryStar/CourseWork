weight = float(input("Enter your weight in pounds: "))
height = float(input("Enter your height in inches: "))
age = float(input("Enter your age in years: "))
gender = input("Enter 'M' if you're a male and 'F' if you're a female: ")
if (gender == 'm')|(gender == 'M'):
    bmr = 66 + (6.3 * weight) + (12.9 * height) - (6.8 * age)
    print(bmr)
elif (gender == 'f')|(gender == 'F'):
    bmr = 655 + (4.3 * weight) + (4.7 * height) - (4.7 * age)
    print(bmr)
else:
    print("Invalid input")





