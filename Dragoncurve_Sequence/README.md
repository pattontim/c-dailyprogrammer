In mathematics the regular paperfolding sequence, also known as the dragon curve sequence, is an infinite automatic sequence of 0s and 1s. At each stage an alternating sequence of 1s and 0s is inserted between the terms of the previous sequence. 

The sequence takes its name from the fact that it represents the sequence of left and right folds along a strip of paper that is folded repeatedly in half in the same direction. If each fold is then opened out to create a right-angled corner, the resulting shape approaches the dragon curve fractal.

### Testing

To compile: gcc dragoncurve_main.c -lm -o dragoncurve

To run: ./dragoncurve \<num>

Example: ./dragoncurve 5

|---|1

|---|110

|---|1101100

|---|110110011100100

|---|1101100111001001110110001100100


