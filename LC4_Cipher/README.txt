Purpose: Provide an interface for basic encryption, decryption, and signing text via the ElsieFour(LC4) cipher

-----------------------------------------------------------------
Task I - Encryption 

to compile: 
gcc cipher_main.c

to run: ./a.out e key  plain

test case: ./a.out e 7dju4s_in6vkecxorlzftgq358mhy29pw#ba the_swallow_flies_at_midnight
sample output: Result: hemmykrc2gx_i3p9vwwitl2kvljiz

-----------------------------------------------------------------
Task II - Decryption

to compile: 
gcc cipher_main.c

to run: ./a.out d key encrypted

test case: ./a.out d 9mlpg_to2yxuzh4387dsajknf56bi#ecwrqv grrhkajlmd3c6xkw65m3dnwl65n9op6k_o59qeq.
sample output: Result: congratulations_youre_a_dailyprogrammer

-----------------------------------------------------------------
Task III - Signing

to compile: 
gcc cipher_main.c

to run: ./a.out s key plain signature <header>


no header test case: ./a.out s xv7ydq#opaj_39rzut8b45wcsgehmiknf26l im_about_to_put_the_hammer_down lrubberduc
no header sample output: "Result: ebzeyqel8qwdzjfihpt#azbvgds94qi6h8tsk6z7b3orhfp"
header test case:./a.out s xv7ydq#opaj_39rzut8b45wcsgehmiknf26l im_about_to_put_the_hammer_down lrubberduc abcdefgh2345678 9
header sample output: "Result: 35q6wghr7ikwu_q9qib_744exjcv_mkrcemynetk4bvjqgd"

-----------------------------------------------------------------
Task IIII - Signature Verification and decoding

to compile: 
gcc cipher_main.c

to run: ./a.out u key plain <header>

test case (header): ./a.out u xv7ydq#opaj_39rzut8b45wcsgehmiknf26l 35q6wghr7ikwu_q9qib_744exjcv_mkrcemynetk4bvjqgd abcdefgh23456789
sample output: "Result: im_about_to_put_the_hammer_down lrubberduc"

------------------------------------------------------------------
Known issues: 

- LC4 uses the # octothorpe character which also corresponds with the comment character on some linux systems, use escape characters if the key starts with #
