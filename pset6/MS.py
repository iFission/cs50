from pprint import pprint # to print matrix row by row

def main():
	m, n = input("Enter m x n matrix, separated by space: ").split() # splits the output into 2 numbers
	m, n = [int(x) for x in [m, n]] # list comprehension, converts to int
	matrix = initialise(m,n)
	matrix = assign(matrix)
	pprint(matrix)
	for r in range(m): # number of times matrix must be reduced / round
		pprint(matrix)
		# print("matrix is",matrix)
		tempMatrix =[]
		rrow=[]
		for y in range(n):
			# print("r is", r, "y is", y, "matrix[",r,"][",y,"] is", matrix[r][y], "matrix[",r,"][",r,"] is", matrix[r][r])
			tempMatrix.append(matrix[r][y]/matrix[r][r])
		rrow.append(tempMatrix)
		# print("rrow is",rrow)
		for x in range(m):
			if x is not r:
				# print("x is",x)
				rrrow =[]
				for y in range(n):
					rrrow.append(matrix[x][y]-matrix[x][r]*rrow[0][y])
				# print("rrrow is",rrrow)
				rrow.append(rrrow)
		matrix = []
		matrix = rrow
	matrix.reverse() # reverse the order of the matrix
	pprint(matrix)

# initialise a mxn matrix with 0s
def initialise(m,n):
	matrixZero = [[0 for x in range(n)] for y in range(m)]
	return matrixZero

def assign(matrixAssigning): # len(matrix) = row, len(matrix[0])= column
	for x in range(len(matrixAssigning)):
		for y in range(len(matrixAssigning[0])):
			matrixAssigning[x][y] = float(input()) # pprint prints in separate rows in float, not int
	return matrixAssigning

# reduces the input row matrix by making the first number 1
#def reduceRow(rowMatrix, r, y):
#	rrow = []
#	rrow.append(rowMatrix[r][y]/rowMatrix[r][r])
#	return rrow

if __name__ == '__main__':
	main()