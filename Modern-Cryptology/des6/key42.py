import numpy as np

##########################################################################################                                               #
# DES variables reference: The DES Algorithm Illustrated -                               #
# https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm               #
##########################################################################################

# Permuted choice 2 for generating sub-keys
PC2 = [14, 17, 11, 24,  1, 5, 
        3, 28 ,15,  6, 21, 10, 
        23, 19, 12,  4, 26, 8, 
        16,  7, 27, 20, 13, 2, 
        41, 52, 31, 37, 47, 55, 
        30, 40, 51, 45, 33, 48, 
        44, 49, 39, 56, 34, 53, 
        46, 42, 50, 36, 29, 32]

# Shifts
shifts = [1, 1, 2, 2, 2, 2, 2, 2,  
          1, 2, 2, 2, 2, 2, 2, 1 ]

##########################################################################################
########################################################################################## 

# The following value is obtained after running cryptanalysis.py

rawKey = "101101111011xxxxxx000111101101110001010111111100" # x is unknown bit

key = ['x' for _ in range(56)]

for i in range(48):
    key[PC2[i]-1] = rawKey[i]

for i in range(6):
    for j in range(shifts[i]):
        a = key[27]
        b = key[55]
        for k in range(27, 0, -1):
            key[k] = key[k-1]
            key[k+28] = key[k+27]

        key[0] = a
        key[28] = b

key = ''.join(key)
print(f"Key with missing bits: \n{key}\n")