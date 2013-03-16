import random
from time import *

def generateMatrix(size):
    matrix = [[0]*size]*size
    matrix =[[random.randrange(0, 10, 1) for row in range(size)] for col in range(size)]

    return matrix

def simpleMultiply (A, B):

    if len(A[0]) != len(B):
      print "Invalid Dimensions"
      return

    matrix = [[0 for row in range(len(B[0]))] for col in range(len(A))]

    for i in range(len(A)):                 # for each row in A
        for j in range(len(B[0])):          # for each column in B
            for k in range(len(A[0])):      # for each column in A
                matrix[i][j] += A[i][k]*B[k][j]  # travel to each kth column in each ith row in A and multiply by each jth column and ith row
    return matrix

def strassenMultiply(A, B):

    # only works for n x n
    size = len(A)

    # 1 x 1
    if (size == 1):
        return A[0][0] * B[0][0]

    ## split each in 4
    a, b, c, d = split(A)
    e, f, g, h = split(B)

    # Strassen's Algo from the Book
    p1 = strassenMultiply(a, subtract(f, h))
    p2 = strassenMultiply(add(a, b), h)
    p3 = strassenMultiply(add(c, d), e)
    p4 = strassenMultiply(d, subtract(g, e))
    p5 = strassenMultiply(add(a, d), add(e, h))
    p6 = strassenMultiply(subtract(b, d), add(g, h))
    p7 = strassenMultiply(subtract(a, c), add(e, f))

    # create the four quadrants of the Strassen
    sa = [[0 for row in range(size/2)] for col in range(size/2)]
    sb = [[0 for row in range(size/2)] for col in range(size/2)]
    sc = [[0 for row in range(size/2)] for col in range(size/2)]
    sd = [[0 for row in range(size/2)] for col in range(size/2)]

    # fill them
    sa = subtract( add(add(p5, p4), p6), p2)
    sb = add(p1, p2)
    sc = add(p3, p4)
    sd = subtract( add(p1, p5), add(p3, p7) )

    # address the second base case where all the quadrants are just numbers, not matricies
    if type(sa) == int:
        return [[sa, sb], [sc, sd]]

    # to combine the s matricies
    outmatrix = [[0 for row in range(len(sa)*2)] for col in range(len(sa)*2)]

    for i in range(len(sa)):
        for j in range(len(sa)):
            outmatrix[i][j] = sa[i][j]
            outmatrix[i][j+len(sa)] = sb[i][j]
            outmatrix[i+len(sa)][j] = sc[i][j]
            outmatrix[i+len(sa)][j+len(sa)] = sd[i][j]

    return outmatrix

# adds two matricies
def add(A, B):

    # just incase
    if type(A) == int:
        return (A + B)

    # only works for n x n
    size = len(A)

    matrix = [[0 for row in range(size)] for col in range(size)]

    for i in range(size):
        for j in range(size):
            matrix[i][j] = A[i][j] + B[i][j]

    return matrix

# subtracts matricies A - B
def subtract(A, B):

    # just incase
    if type(A) == int:
        return (A - B)

    # only works for n x n
    size = len(A)

    matrix = [[0 for row in range(size)] for col in range(size)]

    for i in range(size):
        for j in range(size):
            matrix[i][j] = A[i][j] - B[i][j]

    return matrix

# splits up a matrix into quadrants of the form:
#       a b
#       c d
def split(A):

    # should be n x n
    height = width = len(A)

    a = [[0 for row in range(width/2)] for col in range(height/2)]
    b = [[0 for row in range(width/2)] for col in range(height/2)]
    c = [[0 for row in range(width/2)] for col in range(height/2)]
    d = [[0 for row in range(width/2)] for col in range(height/2)]


    for i in range(len(A)):
        for j in range(len(A[0])):
            if (i < width/2 ) & (j < height/2 ):
                a[i][j] = A[i][j]

            if (i < width/2) & (j >= height/2-1):
                assert(i<width/2)
                b[i][j - height/2] = A[i][j]

            if (i >= width/2-1) & (j < height/2):
                c[i - width/2][j] = A[i][j]

            if (i >= width/2-1) & (j >= height/2-1):
                d[i - width/2][j - height/2] = A[i][j]
                #print "height=", height, " width=", width, "i=", i, " j=", j, " A[i][j]=", A[i][j]

    return a, b, c, d

# testing

print "matrix size, simple time, strassen time"

i=8

A = generateMatrix(2**i)
B = generateMatrix(2**i)

starta = clock()
simpleMultiply(A, B)
stopa = clock()

startb = clock()
strassenMultiply(A, B)
stopb = clock()

print (2**i), ", ", stopa-starta, ", ", stopb-startb



