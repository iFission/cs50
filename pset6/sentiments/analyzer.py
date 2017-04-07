import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # assign each line of word from positive.txt to pos as a list, line = readline()
        # possible to use nltk.tokenize.TweetTokenizer() as well
        self.pos = [line.rstrip() for line in open(positives) if not (line.startswith(";") or line.startswith("\n"))]
        self.neg = [line.rstrip() for line in open(negatives) if not (line.startswith(";") or line.startswith("\n"))]

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        # print(text)
        # tokenizer splits text into chunks
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        # tokens = nltk.tokenize.TweetTokenizer.tokenize(text)
        # print(tokens)
        sum = 0
        for i in range(len(tokens)):
            if tokens[i] in self.pos:
                sum = sum + 1
            elif tokens[i] in self.neg:
                sum = sum - 1
            # else:
                # sum = sum
        # print(sum)
        return sum