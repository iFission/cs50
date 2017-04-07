import sys
import string

def main():
	for i in range(26):
			strK = string.ascii_letters[i]
			print(strK)

	for i in range(26):
			for j in range(26):
				strK = string.ascii_letters[i] + string.ascii_letters[j]
				print(strK)

	for i in range(26):
			for j in range(26):
				for k in range(26):
					strK = string.ascii_letters[i] + string.ascii_letters[j] + string.ascii_letters[k]
					print(strK)

	for i in range(26):
			for j in range(26):
				for k in range(26):
					for l in range (26):
						strK = string.ascii_letters[i] + string.ascii_letters[j] + string.ascii_letters[k] + string.ascii_letters[l]
						print(strK)
if __name__ == '__main__':
	main()
	