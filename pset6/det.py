#!/usr/bin/env python3
from pprint import pprint # to print matrix row by row

def main():
	n = input("Enter for n x n matrix:") # splits the output into 2 numbers
	n = int(n) # converts to int
	matrix = initialise(n,n)
	matrix = assign(matrix)
	pprint(matrix)

# initialise a mxn matrix with 0s
def initialise(m,n):
	matrixZero= [[0 for x in range(n)] for y in range(m)]
	return matrixZero

def assign(matrixAssigning): # len(matrix) = row, len(matrix[0])= column
	for x in range(len(matrixAssigning)):
		for y in range(len(matrixAssigning[0])):
			matrixAssigning[x][y] = int(input())
	return matrixAssigning

# reduces the input row matrix by making the first number 1
#def reduceRow(rowMatrix, r, y):
#	rrow = []
#	rrow.append(rowMatrix[r][y]/rowMatrix[r][r])
#	return rrow
	
if __name__ == '__main__':
	main()