class rational:
    def __init__(self,num=0,den=0):
        self.numerator = num
        self.denominator = den
    def __str__(self):
        a = self.numerator
        b = self.denominator
        if b == 0:
            return "0"
        elif a%b == 0:
            return str(a//b)
        else:
            return str(self.numerator) + '/' + str(self.denominator)
