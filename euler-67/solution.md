## Solution

When thinking about a solution to the problem it quickly becomes obvious that this can hardly be solved by a traditional path-finding algorithm like depth-first-search, as a single large number somewhere in the pyramid can alter the result significantly.

If we give the following input,
```
    1
   7 9
  2 4 9
80 5 2 9
```
the algorithm can not (in polynomial time) anticipate the `80` at the bottom and will choose the path full of `9`, which, to a human eye, is obviously the wrong choice.

I'll try to solve this using _dynamic programming_. S. Dasgupta, C.H. Papadimitriou, and U.V. Vazirani call it _a sledgehammer of the algorithm craft_, and with good reason. If you're not familiar with dynamic programming, I can highly recommend their book [Algorithms](http://beust.com/algorithms.pdf).
