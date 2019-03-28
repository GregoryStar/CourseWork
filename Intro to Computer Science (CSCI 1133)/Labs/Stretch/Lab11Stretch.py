class measure:
    def __init__(self, feet = 0, inches = 0):
        if not(feet == 0 and inches == 0):
            while inches > 11:
                inches -= 12
                feet += 1
            while inches < 0:
                inches += 12
                feet -= 1
            self.feet = abs(feet)
            self.inches = abs(inches)
        else:
            self.feet = feet
            self.inches = inches
    def __str__(self):
        feet = self.feet
        inches = self.inches
        if feet == 0 and inches == 0:
            return '0"'
        elif feet == 0:
            return str(inches) + '"'
        else:
            return str(feet) + "' " + str(inches) + '"'
    def __add__(measure1, measure2):
        feet = measure1.feet + measure2.feet
        inches = measure1.inches + measure2.inches
        return str(measure(feet, inches))
    def __sub__(measure1, measure2):
        feet = measure1.feet - measure2.feet
        inches = measure1.inches - measure2.inches
        return str(measure(feet, inches))

def measureTest():
    m1 = measure()
    m2 = measure(4,11)
    m3 = measure(6,10)
    print(m1)
    print(m2+m3)
    print(m3-m2)
