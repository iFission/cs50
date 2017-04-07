import sys

def main():
	if len(sys.argv) == 2:
		for c in sys.argv[1]:
			if not c.isalpha():
				return 1
		strP = input()

		i = 0

		for c in strP:
			if i < len(sys.argv[1]):
				if sys.argv[1][i].isupper():
					k = ord(sys.argv[1][i]) - ord('A')
				else:
					k = ord(sys.argv[1][i]) - ord('a')

			if c.isalpha():
				if c.isupper():
					c = ((ord(c) + k - ord('A')) % 26) + ord('A')
				else:
					c = ((ord(c) + k - ord('a')) % 26) + ord('a')
				c = chr(c)
				i += 1

			print(c, end='')
			if i >= len(sys.argv[1]):
				i = i - len(sys.argv[1])

	else:
		return 1

if __name__ == "__main__":
	main()