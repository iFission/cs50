def main():
	height = get_positive_int()
	
	for row in range(height):
		space = height - row - 1
		block = row + 2
		printSpace(space)
		printBlock(block)
		printSpace(2)
		printBlock(block)
		printSpace(space)
		print()

def get_positive_int():
	while True:
		print("n is ", end="")
		n = int(input())
		if n >= 1 and n <= 23:
			return n

def printSpace(n):
	for i in range(n):
		print(" ", end="")

def printBlock(n):
	for i in range(n):
		print("#", end="")

if __name__ == "__main__":
	main()