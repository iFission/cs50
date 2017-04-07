def main():
	height = get_positive_int()
	
	for row in range(height):
		space = height - row - 1
		block = row + 2
		for n in range(space):
			print(" ", end="")
		for n in range (block):
			print("#", end="")
		print()

def get_positive_int():
	while True:
		print("n is ", end="")
		n = int(input())
		if n >= 1 and n <= 23:
			return n

if __name__ == "__main__":
	main()