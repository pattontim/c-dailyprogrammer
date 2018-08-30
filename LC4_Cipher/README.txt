Purpose: Provide an interface for basic encryption, decryption, and signing text via the ElsieFour(LC4) cipher

Task I - Encryption 

to compile: 
gcc cipher_main.c

to run: ./a.out e key  plain

test case: ./a.out e 7dju4s_in6vkecxorlzftgq358mhy29pw#ba the_swallow_flies_at_midnight
sample output: Result: hemmykrc2gx_i3p9vwwitl2kvljiz

Task II - Decryption

to compile: 
gcc cipher_main.c

to run: ./a.out d key encrypted

test case: ./a.out d 9mlpg_to2yxuzh4387dsajknf56bi#ecwrqv grrhkajlmd3c6xkw65m3dnwl65n9op6k_o59qeq.
sample output: Result: congratulations_youre_a_dailyprogrammer

Known issues: 

- LC4 uses the # octothorpe character which also corresponds with the comment character on some linux systems, use escape characters if the key starts with #
