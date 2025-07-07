import math

phrase = input("Type your phrase : ")

words = len(phrase.split())
spaces = len(phrase.split()) - 1
letters = sum(1 for c in phrase if c.isalpha())
sentences = sum(1 for c in phrase if c in ['.', '!', '?'])

l = 100 * letters / words
s = 100 * sentences / words

grade = 0.0588 * l - 0.296 * s - 15.8
grade_floored = math.floor(grade)
decimal = grade - grade_floored

grade = grade_floored + 1 if decimal > 0.5 else grade_floored

if grade < 0:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
