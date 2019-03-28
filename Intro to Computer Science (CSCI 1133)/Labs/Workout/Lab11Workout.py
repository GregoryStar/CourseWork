import math
class vec3:
    def __init__(vector, vecList = [0,0,0]):
        vector.vecList = vecList

    def __str__(vector):
        string = "["
        vectorList = vector.vecList
        for element in vectorList:
            string += str(element) + ", "
        string = string[:len(string) - 2] + "]"
        return string
        
    def vlist(vector):
        return vector.vecList
    def setValues(vector, newList):
        vector.vecList = newList
    def __float__(vector):
        vectorList = vector.vecList
        accum = 0
        for element in vectorList:
            accum += element ** 2
        return math.sqrt(accum)
    def __sum__(vector1, vector2):
        list1 = vector1.vecList
        list2 = vector2.vecList
        newList = []
        for i in range(0, len(list1)):
             newList.append(list1[i] + list2[i])
        return vec3(newList)                   
            
    def __truediv__(vector, scalar):
        oldList = vector.vecList
        newList = []
        for element in oldList:
            newList.append(element/scalar)
        return vec3(newList)
forceVec = vec3([10,20,30])
mass = 10
accel = forceVec/mass
print(accel, float(accel))
