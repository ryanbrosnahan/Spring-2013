import random
import time

def generateMatrix(size):
    matrix = [[0]*size]*size
    matrix =[[random.randrange(0, 10, 1) for row in range(size)] for col in range(size)]

    return matrix

def basicMultiply(A, B):

    print A
    print B

    if len(A[0]) != len(B):
        print "Invalid Dimensions"
        return

    matrix = [[0]*len(A)]*len(B[0])
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                matrix[i][j] += A[i][k]*B[k][j]

    return matrix

print basicMultiply( generateMatrix(4), generateMatrix(4) )