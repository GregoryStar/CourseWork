cards = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
values = [2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11]
inValues = []
entering = True
while entering:
    x = input("Enter a card (enter 'stop' to quit): ")
    if x == 'stop':
        entering = False
    else:
        inValues.append(x)
total = 0
z = 0
for n in inValues:
    if (n == 'A') & (total > 10):
        total += 1
    else:
        pos = 0
        for i in range(0, len(cards)):
            if inValues[z] == cards[i]:
                pos = i
        total += values[pos]
        z += 1       

print(total)
        
