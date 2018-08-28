Purpose: Provide an interface for basic encryption and decryption of the ElsieFour(LC4) cipher.

Task I - Encryption 

to compile: 
gcc cipher_main.c

to run: ./a.out key %plain 

test case: ./a.out 7dju4s_in6vkecxorlzftgq358mhy29pw#ba %the_swallow_flies_at_midnight
sample output: Encrypted: hemmykrc2gx_i3p9vwwitl2kvljiz

Task II - Decryption

to compile: 
gcc cipher_main.c

to run: ./a.out key encrypted

test case: ./a.out 9mlpg_to2yxuzh4387dsajknf56bi#ecwrqv grrhkajlmd3c6xkw65m3dnwl65n9op6k_o59qeq.
sample output: Decrypted: congratulations_youre_a_dailyprogrammer

Known issues: 

- LC4 uses the # octothorpe character which also corresponds with the comment character on some linux systems, use escape characters if the key starts with #
