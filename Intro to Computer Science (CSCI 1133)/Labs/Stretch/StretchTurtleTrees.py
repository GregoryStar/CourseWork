import turtle
import random

def tree(t, trunkLength):
    if trunkLength < 5:
        return
    else:
        angle = random.randint(15, 45)
        length = random.randint(12, 18)
        t.forward(trunkLength)
        t.right(angle)
        tree(t, trunkLength-length)
        t.left(angle * 2)
        tree(t, trunkLength-length)
        t.right(angle)
        t.backward(trunkLength)

a = turtle.Turtle()
a.speed(100)
tree(a, 100)
