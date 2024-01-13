#

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def solve1() -> bool:
    return True

def main():
    t: int = int(input())
    for _ in range(t):


        if solve1():
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
