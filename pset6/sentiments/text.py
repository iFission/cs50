import os
import sys

def main():
	positives = os.path.join(sys.path[0], "positive-words.txt")
	negatives = os.path.join(sys.path[0], "negative-words.txt")
	analyzer = Analyzer(positives, negatives)

def Analyzer(positives, negatives):
	# assign each line of word from positive.txt to pos as a list, line = readline()
	pos = [line.rstrip() for line in open(positives) if not (line.startswith(";") or line.startswith("\n"))]
	neg = [line.rstrip() for line in open(negatives) if not (line.startswith(";") or line.startswith("\n"))]

if __name__ == '__main__':
	main()