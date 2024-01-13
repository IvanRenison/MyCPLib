#

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def solve():
    pass

def main():


    ans = solve()
    print(ans)


if __name__ == '__main__':
    main()
