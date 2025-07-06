while (True):
    try:
        bricks = int(input("How many bricks high ? : "))
    except:
        print("Non numeric value")
    else:
        if bricks in range(1, 9):
            break


for i in range(bricks):
    print(" " * (bricks-i-1), end="")
    print("#" * (i+1), end="")
    print("  ", end="")
    print("#" * (i+1))
