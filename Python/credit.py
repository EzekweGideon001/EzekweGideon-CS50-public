# Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois

def main():
    # Get the number
    number = input("Number: ")
    length = len(number)
    is_valid = luhn_alg(number)

    if is_valid == False:
        print("INVALID")
    else:
        # I learn this slicing techinque learnt from Programming with Mosh (YouTube channel)
        if length == 15 and number[0:2] in ["34", "37"]:
            print ("AMEX")
        elif length == 16 and number[0:2] in ["51","52","53","54","55"]:
            print("MASTERCARD")
        elif (length == 13 or length == 16) and number[0] == "4":
            print("VISA")
        else:
            print("INVALID")


# Carry out Luhn's algorithm
def luhn_alg(number):
    # reverse the string. Techinque learnt from Programming with Mosh (YouTube channel)
    rev_number = number[::-1]

    # Loop through the digits by 2 steps and multiply each by 2
    count = 0
    for i in range (1, len(rev_number), 2):
        mult_digit = int(rev_number[i]) * 2
        # Check if result is greater than 9. Subtracting 9 gives the same result as adding both individual digits together.
        if mult_digit > 9:
            mult_digit -= 9
        count += mult_digit

    # Loop through to add the non-multiplied digits
    sum_count = 0
    for i in range (0, len(rev_number), 2):
        sum_count += int(rev_number[i])

    # Add the final sum of both
    total = sum_count + count

    # Return true or false depending on divisibility by 10
    return total % 10 == 0

# Call main function
main()
