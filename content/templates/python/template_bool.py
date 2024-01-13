#

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def solve() -> bool:
    return True

def main():


    if solve():
        print("Yes")
    else:
        print("No")


if __name__ == '__main__':
    main()
