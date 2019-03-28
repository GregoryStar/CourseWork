d = int(input("Input a day: "))
m = int(input("Input a month: "))
y = int(input("Input a year: "))
if (m == 1)|(m == 2) :
    m += 12
    y -= 1
day = (d + 5 + ((26*(m + 1))//10) + ((5*(y%100))//4) + ((21*(y//100))//4))%7
days = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
print(days[day])
