import sys

def main():
	if len(sys.argv) == 2:
		k = int(sys.argv[1])%26

		strP = input()

		for c in strP:
			if c.isalpha():
				if c.isupper():
					c = ((ord(c) + k - ord('A')) % 26) + ord('A')
				else:
					c = ((ord(c) + k - ord('a')) % 26) + ord('a')
				c = chr(c)
			print(c, end='')
	else:
		return 1

if __name__ == "__main__":
	main()