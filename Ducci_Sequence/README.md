Purpose: Calculates the number of steps required to solve a Ducci Sequence, according to the following rules. [Challenge Details](https://www.reddit.com/r/dailyprogrammer/comments/8sjcl0/20180620_challenge_364_intermediate_the_ducci/)

The Ducci Sequence here is converted into phases through which it passes as it tends towards a pattern.

The reduction phase is active when the numbers at an stage in the sequence are not binary. Here, binary is defined as the numbers of the sequence all being the same constant, ie (2,2,2,0,2) or (1,0,1). This functionality is provided by the advancePrimitive and sequence storage structures.

The binary phase is active when all the numbers are binary, in which case the algorithm checks for a pattern.

The sequence terminates when it is zero or repeating.

#### Task I - Calculate and display steps to reach Ducci Sequence

to compile:
make clean

make

To run: ./ducci.o
output: Each step made in the sequence and the # of sequences at the end

#### Known issues
- Needs better window size algorithm

#### Planned features
- Enter ducci sequence via terminal
