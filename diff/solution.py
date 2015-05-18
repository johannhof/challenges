# Diffing algorithm

# Create a visual diff between two texts (original and edit)
# This algorithm also determines their edit distance
# (number of edit steps to make them equal again)

# This problem reduces to LCS, which is a shortest-path problem
# LCS solving is done using the simple variant of the algorithm
# proposed in http://www.xmailserver.org/diff2.pdf

# merges two versions of a text based on an lcs
# additions and deletions are colored differently
def merge(orig, edit, lcs, add_color, rem_color):
    add = []
    i = 0
    j = 0
    for c in lcs:
        while i < len(orig) and c != orig[i]:
            add.append(rem_color + orig[i] + '\033[0m')
            i += 1
        while j < len(edit) and c != edit[j]:
            add.append(add_color + edit[j] + '\033[0m')
            j += 1

        add.append(c)
        i += 1
        j += 1

    while i < len(orig):
        add.append(rem_color + orig[i] + '\033[0m')
        i += 1
    while j < len(edit):
        add.append(add_color + edit[j] + '\033[0m')
        j += 1

    return ''.join(add)


# Calculates the longest common subpath
def lcs(orig, edit):
    # length of the first word
    N = len(orig)
    # length of the second word
    M = len(edit)

    # combined length
    MAX = N + M

    # helper array to hold furthest points on diagonal k
    # will be overwritten every second iteration of D
    v = range(-MAX, MAX)

    # helper array to keep letters that are not different
    common = []

    # provide a starting point
    v[1] = 0

    # iterate over edit steps D
    # with each step, the edit differs more from the original
    for D in range(0, MAX):

        # helpers to get hold of the longest possible snake
        max = 0
        max_snake = []

        # iterate over the diagonals to find which one is best
        for k in range(-D, D + 1, 2):
            # a snake is a chain of text that both texts have in common
            # (a chain of diagonals after a horizontal or vertical)
            snake = []

            x = 0
            # choose the previous best = furthest starting point
            # from the two adjacent diagonals
            if k == -D or k != D and v[k - 1] < v[k + 1]:
                x = v[k + 1]
            else:
                x = v[k - 1] + 1

            # calculate y
            y = x - k

            # walk that diagonal as long as possible
            while x < N and y < M and orig[x] == edit[y]:
                snake.append(orig[x])
                x += 1
                y += 1

            # record furthest reaching D-path in diagonal k
            v[k] = x
            if x > max:
                max_snake = snake
                max = x

            # as proven in the paper, if we reach the boundary of the graph
            # we have found the lcs
            if x >= N and y >= M:
                common += max_snake

                print(merge(orig, edit, common, '\033[91m', '\033[92m'))
                return D

        common += max_snake

lcs("The quick brown fox jumps over the lazy dog", "The quick brown dog leaps over the lazy cat")
