function hp(x,y,data)
  len = size (data[y],1)

  if x == 1
    return data[y-1][1]
  end

  if x == len
    return data[y - 1][size(data[y-1],1)]
  end

  p1 = data[y-1][x - 1]
  p2 = data[y-1][x]

  if p1 > p2
    return p1
  else
    return p2
  end
end


input = readlines(open("triangle.txt", "r"))
n = size(input, 1)
show(n)

data = Array (Array, 100)

for i = 1:n
  data[i] = map((x) -> parse (x) , split(input[i]))
end

res = Array (Array, 100)

res[1] = data[1]

for i = 2:n
  res[i] = Array (Int64, i)
end

for y = 2:n
  cur = data[y]
  len = size (cur,1)
  for x = 1:len
    p = hp (x,y,res)
    res[y][x] = data[y][x] + p
  end
end

show (res[n][indmax(res[n])])
