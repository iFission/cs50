def main():
	change = get_positive_float()
	changeCent = change*100

	coinNum = 0
	coinNumQuarter = 0
	coinNumDime = 0
	coinNumNickel = 0
	coinNumPenny = 0

	while (changeCent>=25): ## quarter
	    changeCent = changeCent-25
	    coinNum=coinNum+1
	    coinNumQuarter=coinNumQuarter+1
	
	while (changeCent>=10): ## dime
	    changeCent = changeCent-10
	    coinNum=coinNum+1
	    coinNumDime=coinNumDime+1
	
	while (changeCent>=5): ## nickel
	    changeCent = changeCent-5
	    coinNum=coinNum+1
	    coinNumNickel=coinNumNickel+1
	
	while (changeCent>=1): ## penny
	    changeCent = changeCent-1
	    coinNum=coinNum+1
	    coinNumPenny=coinNumPenny+1
	
	print("{}".format(coinNum))

def get_positive_float():
	while True:
		n = float(input())
		if n > 0:
			return n

if __name__ == "__main__":
	main()