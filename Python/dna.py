# Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) < 3:
        print ("Usage: python dna.py file.csv file.txt")
        sys.exit(1)
    database = sys.argv[1]
    sequence = sys.argv[2]
    rows = []

    # Read database file into a variable
    with open(database) as file:
        reader = csv.DictReader(file)
        str_fields = reader.fieldnames[1:]  # The first column is the individual's name, rest are STRs
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable
    with open(sequence) as file:
        dna_sequence = file.read().rstrip()

    # Find longest match of each STR in DNA sequence
    # Initialize an empty list to store the counts
    str_count = []

    # Loop over each STR field
    for str_field in str_fields:
        count = longest_match(dna_sequence, str_field)  # Find the longest match for the current STR
        str_count.append(count)


    # Check database for matching profiles
    for row in rows:
        match = True
        # Usage of enumerate function was learnt from a prior course.
        for i, str_field in enumerate(str_fields):
            if int(row[str_field]) != str_count[i]:
                match = False
                break  # Exit the inner loop

        if match:
            # If all STR counts match, print the name and exit
            print(f"{row['name']}")
            return

    # If no profile match was found after checking all the rows
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
