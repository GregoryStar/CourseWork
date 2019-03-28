import math
listOfPoints = [[45, -99], [24, 83], [-48, -68], [-97, 99], [-8, -77], [-2, 50], [44, 41], [-48, -58],[-1, 53], [14, 86], [31, 94], [12, -91],[33, 50], [82, 72], [83, -90], [10, 78],[7, -22], [90, -88], [-21, 5], [6, 23]]
print(listOfPoints)
def shortestDist(points):
    dists = []
    for pair in points:
        for pair2 in points:
            if pair != pair2:
                distx = pair[0] - pair2[0]
                disty = pair[1] - pair2[1]
                dist = math.sqrt(distx ** 2 + disty **2)
                dists.append(dist)
    return min(dists)
x = shortestDist(listOfPoints)
print(x)
