A Kolakoski sequence (A000002) is an infinite sequence of symbols {1, 2} that is its own run-length encoding. It alternates between "runs" of symbols. The sequence begins:

12211212212211211221211212211...

The first three symbols of the sequence are 122,
which are the output of the first two iterations.
After this, on the i-th iteration read the value x[i]
of the output (one-indexed). If i is odd, output x[i]
copies of the number 1. If i is even, output x[i]
copies of the number 2.

In the code representation, 0=1 and 1=2 in order to utilize boolean logic. Furthermore, the latest iteration is stored in a deque

### Testing

to compile: g++ main.cpp -o kolakoski

to test: ./kolakoski

You may modify the number of iterations to run by changing ITERATIONS at the top of the source file.

### Considerations

Todo:

- Implement command line input
- Simplify counting into pair 
- Test data structure speed and optimize

Known Problems