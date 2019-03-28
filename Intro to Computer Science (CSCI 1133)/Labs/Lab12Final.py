import turtle
import random
import math
def randColor():
    colorList = ["red", "yellow", "green", "blue", "purple", "orange"]
    i = random.randint(0, len(colorList) - 1)
    return colorList[i]
class Shape(object):
    def __init__(self, x, y, fillColor = "", filled = True):
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
        super().__init__(x, y, fillColor)
        self.r = r

    def draw(self, turtle):
        turtle.penup()
        turtle.goto(self.x, self.y - self.r)
        turtle.pendown()
        if self.filled:
            turtle.fillcolor(self.fillColor)
            turtle.begin_fill()
            turtle.circle(self.r)
            turtle.end_fill()
        else:
            turtle.circle(self.r)

    def isIN(self, x, y):
        r = self.r
        d = math.sqrt((x - self.x) ** 2 + (y - self.y) ** 2)
        if d < r:
            return True
        else:
            return False

class rectangle(Shape):
    def __init__(self, x, y, width, height, fillColor = "red"):
        super().__init__(x, y, fillColor)
        self.width = width
        self.height = height

    def draw(self, turtle):
        turtle.penup()
        turtle.goto(self.x - 0.5 * self.width, self.y + 0.5 * self.height)
        turtle.pendown()
        if self.filled:
            turtle.fillcolor(self.fillColor)
            turtle.begin_fill()
            turtle.forward(self.width)
            turtle.right(90)
            turtle.forward(self.height)
            turtle.right(90)
            turtle.forward(self.width)
            turtle.right(90)
            turtle.forward(self.height)
            turtle.right(90)
            turtle.end_fill()
        else:
            turtle.forward(self.width)
            turtle.right(90)
            turtle.forward(self.height)
            turtle.right(90)
            turtle.forward(self.width)
            turtle.right(90)
            turtle.forward(self.height)
            turtle.right(90)

    def isIN(self, x, y):
        h = self.height
        w = self.width
        cx = self.x
        cy = self.y
        if (abs(x - cx) < w/2) and (abs(y - cy) < h/2):
            return True
        else:
            return False
            
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
        isIn = False
        for element in self.elements:
            if element.isIN(x, y):
                isIn = True
                self.remove(element)
        if not isIn:
            a = random.randint(0,1)
            if a == 0:
                i = random.randint(10, 100)
                circ = circle(x, y, i, randColor())
                display.add(self, circ)
            else:
                h = random.randint(20, 200)
                w = random.randint(20, 200)
                rect = rectangle(x, y, h, w, randColor())
                display.add(self, rect)

    def add(self, shape):
        self.elements.append(shape)
        shape.draw(self.turt)
    def remove(self, shape):
        for element in self.elements:
            if element == shape:
                self.elements.remove(element)
        self.turt.clear()
        for element in self.elements:
            element.draw(self.turt)
