import random
selection = input("Would you like to go first(y/n)?")
remaining = 21

if selection == "y":
    iLose = False
    print("not a choice yet")
    while remaining > 0:
        validInput = False
        while not validInput:
            print(remaining)
            choice = int(input(" objects remain, choose 1,2, or 3:"))
            if 0 < choice < 4:
                validInput = True
                remaining -= choice
            else:
                print("Not valid input, moron")
        if (remaining > 0):
            if (remaining % 4) > 0:
                iChoose = remaining % 4
                print("ok, Ill take ", iChoose)
                remaining -= iChoose
            else:
                iChoose = random.randint(1,3)
                print("ok, Ill take ", iChoose)
                remaining -= iChoose
        else:
            print("I lose!")
            iLose = True
    if not iLose:
        print("I win. Thanks for playing!")

elif selection == "n":
    while remaining > 0:
        iChoose = remaining % 4
        print("ok, Ill take ", iChoose)
        remaining -= iChoose
        if (remaining > 0):
            validInput = False
            while not validInput:
                print(remaining)
                choice = int(input(" objects remain, choose 1,2, or 3:"))
                if 0 < choice < 4:
                    validInput = True
                    remaining -= choice
                else:
                    print("Not valid input, moron")
        else:
            print("I win. Thanks for playing!")
else:
    print("Invalid Input!")

        
