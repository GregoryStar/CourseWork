def drawsquare(aturtle, sideLength):
    for i in range (0, 4):
        aturtle.forward(sideLength)
        aturtle.right(90)

def drawFlowerSquare(aturtle, sideLength, numSquares):
    for i in range (0, numSquares):
        drawsquare(aturtle, sideLength)
        aturtle.right(360/numSquares)
        

import turtle
myturtle = turtle.Turtle()
numberOfSquares = int(input("Enter a number of squares: "))
drawFlowerSquare(myturtle, 100, numberOfSquares)
