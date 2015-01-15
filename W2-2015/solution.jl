# a function to find the highest parent element
function hp(x,y,prow)
  if x == 1
    return prow[1]
  end

  if x > size(prow,1)
    return prow[size(prow,1)]
  end

  p1 = prow[x - 1]
  p2 = prow[x]

  return p1 > p2 ? p1 : p2
end

# read from input file
input = readlines(open("triangle.txt", "r"))

n = size(input, 1)

# initialize data containers
data = Array (Array, 100)
opt = Array (Array, 100)

# transform input to fit data model
for i = 1:n
  data[i] = map((x) -> parse (x) , split(input[i]))
end

# satisfy our base case
opt[1] = data[1]

# the actual recurrence
for y = 2:n
  opt[y] = [ data[y][x] + hp(x,y,opt[y-1]) for x = 1:size(data[y],1) ]
end

# print out the result
# i have no idea why max(array) did not work for me
print(opt[n][indmax(opt[n])])
