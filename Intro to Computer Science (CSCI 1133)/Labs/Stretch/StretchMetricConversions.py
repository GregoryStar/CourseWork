print("This program converts an inputed amount from one unit to another.")
unit = input("Input the unit you're converting from: ")
x = float(input("Input the amount: "))
recUnits = ['pounds', 'ounces', 'miles', 'inches', 'kilos', 'grams', 'kilometers', 'centimeters']
if not (unit in recUnits):
    print("Invalid input: ")
elif unit == 'pounds':
    print((x * 0.0454), " kilograms")
elif unit == 'ounces':
    print((x * 28.350), " grams")
elif unit == 'miles':
    print((x * 1.609), " kilometers")
elif unit == 'inches':
    print((x * 2.54), " centimeters")
elif unit == 'kilos':
    print((x * 2.205), " pounds")
elif unit == 'grams':
    print((x * 0.035), " ounces")
elif unit == 'kilometers':
    print((x * 0.621), " miles")
elif unit == 'centimeters':
    print((x * 0.394), " inches")
