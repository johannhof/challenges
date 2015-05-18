def merge(a, b, color):
    add = []
    i = 0
    for c in a:
        if c != b[i]:
            add.append(color + c + '\033[0m')
        else:
            add.append(b[i])
            i += 1

    return ''.join(add)

"""
This problem reduces to LCS, which is a shortest-path problem
"""
def distance(a, b):
    # length of the first word
    N = len(a)
    # length of the second word
    M = len(b)

    # combined length
    MAX = N + M

    v = range(-MAX, MAX)

    res_a = ""
    res_b = ""

    # provide a starting point
    v[1] = 0

    seq = []

    for D in range(0, MAX):
        max = 0
        max_snake = []

        # iterate over the diagonals to find which one is best
        for k in range(-D, D + 1, 2):
            snake = []

            x = 0
            # choose the previous best = furthest starting point
            # from the two adjacent diagonals
            if k == -D or k != D and v[k - 1] < v[k + 1]:
                x = v[k + 1]
            else:
                x = v[k - 1] + 1

            y = x - k

            # walk that diagonal as long as possible
            while x < N and y < M and a[x] == b[y]:
                snake.append(a[x])
                x += 1
                y += 1

            # record furthest reaching D-path in diagonal k
            v[k] = x
            if x > max:
                max_snake = snake
                max = x

            if x >= N and y >= M:
                seq += max_snake

                print(merge(a, seq, '\033[92m'))
                print(merge(b, seq, '\033[91m'))
                return (D, merge(a, seq, '\033[92m'))

        seq += max_snake

print("dist", distance("i quest this now", "i test this now"))
