def main():
	i = get_positive_int()
	print("{}".format(i))

def get_positive_int():
	while True:
		print("n is ", end="")
		n = int(input())
		if n>= 1:
			return n

if __name__ == "__main__":
	main()