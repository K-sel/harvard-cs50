import csv
import sys


def main():

    if len(sys.argv) == 3:

        with open(sys.argv[1]) as csv_file:
            csv_reader = csv.DictReader(csv_file)
            people = list(csv_reader)
            STR_sequences = csv_reader.fieldnames[1:]


        with open(sys.argv[2]) as textfile:
            STR = textfile.read()

    else:
        print("Args not valid")

    STR_counts = {}
    for sequence in STR_sequences:
        STR_counts[sequence] = longest_match(STR, sequence)

    for person in people:
        match = all(
            int(person[sequence]) == STR_counts[sequence]
            for sequence in STR_counts
            )
        if match:
            print(f"{person['name']}")
            return

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
