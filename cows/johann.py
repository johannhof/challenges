array = [True, True, True, False, True, True, False, False, True, True, False, True]

# the last spot where a cow was
last = 0
opt = [5]

for i in range(len(array)):
    if array[i]:
        opt.append(3 + min(opt[last] + 5, opt[last] + 3 * (i - last)))
        last = i + 1
    else:
        opt.append(opt[last])

print opt[len(array)]
