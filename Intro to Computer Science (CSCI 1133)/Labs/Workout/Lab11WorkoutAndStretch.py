import turtle
import random
def randColor():
    colorList = ["red", "yellow", "green", "blue", "purple", "orange"]
    i = random.randint(0, len(colorList) - 1)
    return colorList[i]
class Shape(object):
    def __init__(self, x = 0, y = 0, fillColor = "", filled = True):
        self.x = x
        self.y = y
        self.fillColor = fillColor
        self.filled = filled
        
    def setFillColor(self, string):
        self.fillColor = string

    def setFilled(self, boolean):
        self.filled = boolean

    def isFilled(self):
        return self.filled

class circle(Shape):
    def __init__(self, x = 0, y = 0, r = 1, fillColor = "red"):
        super().__init__()
        self.r = r
        self.x = x
        self.y = y
        self.fillColor = fillColor

    def draw(self, turtle):
        turtle.penup()
        turtle.goto(self.x, self.y)
        turtle.pendown()
        if self.filled:
            turtle.fillcolor(self.fillColor)
            turtle.begin_fill()
            turtle.circle(self.r)
            turtle.end_fill()
        else:
            turtle.circle(self.r)

class display(object):
    def __init__(self):
        self.turt = turtle.Turtle()
        self.turt.speed(0)
        self.turt.hideturtle()
        self.scrn = turtle.Screen()
        self.scrn.delay(0)
        self.scrn.onclick(self.mouseEvent)
        self.scrn.listen()
        self.elements = []

            
    def mouseEvent(self, x, y):
        i = random.randint(10, 100)
        circ = circle(x, y, i, randColor())
        circ.draw(self.turt)

