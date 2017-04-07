def main():
	cardID = input("")
	length = len(cardID)
	checksum = 0
	for index2 in range((length - 2), -1, -2): # select the every other digit, starting with second last digit
		temp = 2 * int(cardID[index2]) # multiply that digit by 2
		# if the product is 2 number, add the numbers together
		if temp > 9:
			temp = int(str(temp)[0]) + int(str(temp)[1])

		checksum = checksum + temp
		#print("{}".format(checksum))

	for index1 in range((length - 1), -1, -2): # select the every other digit, starting with last digit
		temp = int(cardID[index1])
		checksum = checksum + temp
		#print("{}".format(checksum))


	if checksum%10 == 0:
		if (((cardID[0] + cardID [1]) == str(34)) or (cardID[0] + cardID [1]) == str(37)):
			print("AMEX")
		if (((cardID[0] + cardID [1]) == str(51)) or (cardID[0] + cardID [1]) == str(52) or (cardID[0] + cardID [1]) == str(53) or (cardID[0] + cardID [1]) == str(54) or (cardID[0] + cardID [1]) == str(55)):
			print("MASTERCARD")
		if (cardID[0] == str(4)):
			print("VISA")

	else:
		print("INVALID")

if __name__ == "__main__":
	main()