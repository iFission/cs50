import sys
import string

def main():
	if len(sys.argv != 1):
		return 1

def strGen():
	for i in range(26):
		for j in range(26):
			for k in range(26):
				for l in range (26):
					strK = string.ascii_letters[i] + string.ascii_letters[j] + string.ascii_letters[k] + string.ascii_letters[l]

	