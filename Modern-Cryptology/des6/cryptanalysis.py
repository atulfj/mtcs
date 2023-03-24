import numpy as np

##########################################################################################                                               #
# DES variables reference: The DES Algorithm Illustrated -                               #
# https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm               #
##########################################################################################

# Bit expansion
E = [32, 1 , 2 , 3 , 4 , 5 , 4 , 5,  
    6 , 7 , 8 , 9 , 8 , 9 , 10, 11,  
    12, 13, 12, 13, 14, 15, 16, 17,  
    16, 17, 18, 19, 20, 21, 20, 21,  
    22, 23, 24, 25, 24, 25, 26, 27,  
    28, 29, 28, 29, 30, 31, 32, 1 ]

# S-boxes
S = [[[14, 4, 13, 1, 2, 15, 11, 8, 3 , 10, 6, 12, 5, 9, 0, 7],
    [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
    [4, 1 , 14, 8, 13, 6, 2, 11, 15, 12, 9, 7,3, 10, 5, 0],
    [15, 12, 8,2,4, 9, 1,7 , 5, 11, 3, 14, 10, 0, 6, 13]],

    [[15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0,5, 10],
    [3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
    [0, 14, 7, 11, 10, 4, 13, 1, 5, 8,12, 6, 9, 3, 2, 15],
    [13, 8, 10, 1, 3, 15, 4, 2,11,6, 7, 12, 0,5, 14, 9]],

    [[10, 0, 9,14,6,3,15,5, 1, 13, 12, 7, 11, 4,2,8],
    [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
    [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12,5, 10, 14, 7],
    [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]],

    [[7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
    [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
    [10, 6, 9, 0, 12, 11, 7, 13, 15, 1 , 3, 14, 5, 2, 8, 4],
    [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]],

    [[2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
    [14, 11,2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
    [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14],
    [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]],

    [[12, 1, 10, 15, 9, 2, 6,8, 0, 13, 3, 4, 14, 7, 5, 11],
    [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
    [9, 14, 15, 5, 2,8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
    [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]],

    [[4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
    [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
    [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
    [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]],

    [[13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12,7],
    [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
    [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
    [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]]]

# Inverse permutation
IP = [9, 17, 23, 31, 13, 28,  2, 18,
	 24, 16, 30,  6, 26, 20, 10, 1,
	 8, 14, 25,  3, 4, 29, 11, 19,
	 32, 12, 22,  7, 5, 27, 15, 21]

# Permuted choice 2 for generating sub-keys
PC2 = [14, 17, 11, 24,  1, 5, 
        3, 28 ,15,  6, 21, 10, 
        23, 19, 12,  4, 26, 8, 
        16,  7, 27, 20, 13, 2, 
        41, 52, 31, 37, 47, 55, 
        30, 40, 51, 45, 33, 48, 
        44, 49, 39, 56, 34, 53, 
        46, 42, 50, 36, 29, 32]

# Initial permutation of DES
P_initial = [58, 50, 42, 34, 26, 18, 10, 2,  
            60, 52, 44, 36, 28, 20, 12, 4,  
            62, 54, 46, 38, 30, 22, 14, 6,  
            64, 56, 48, 40, 32, 24, 16, 8,  
            57, 49, 41, 33, 25, 17, 9,  1,  
            59, 51, 43, 35, 27, 19, 11, 3,  
            61, 53, 45, 37, 29, 21, 13, 5,  
            63, 55, 47, 39, 31, 23, 15, 7]

# Final permutation of DES
P_final = [40, 8, 48, 16, 56, 24, 64, 32,  
          39, 7, 47, 15, 55, 23, 63, 31,  
          38, 6, 46, 14, 54, 22, 62, 30,  
          37, 5, 45, 13, 53, 21, 61, 29,  
          36, 4, 44, 12, 52, 20, 60, 28,  
          35, 3, 43, 11, 51, 19, 59, 27,  
          34, 2, 42, 10, 50, 18, 58, 26,  
          33, 1, 41, 9, 49, 17, 57, 25 ]

# Reverse final permutation
P_rev_final = [57, 49, 41, 33, 25, 17, 9,  1,
              59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5,
              63, 55, 47, 39, 31, 23, 15, 7,
              58, 50, 42, 34, 26, 18, 10, 2,
              60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6,
              64, 56, 48, 40, 32, 24, 16, 8]

# S-Box permuation
P_sbox = [16, 7, 20, 21, 29, 12, 28, 17,  
         1, 15, 23, 26,  5, 18, 31, 10,  
         2,  8, 24, 14,  32, 27, 3,  9,  
         19, 13, 30,  6, 22, 11,  4, 25] 

# Shifts
shifts = [1, 1, 2, 2, 2, 2, 2, 2,  
          1, 2, 2, 2, 2, 2, 2, 1 ]

# Key compression logic table
key_compress = [14, 17, 11, 24, 1, 5,  
                3, 28, 15, 6, 21, 10,  
                23, 19, 12, 4, 26, 8,  
                16, 7, 27, 20, 13, 2,  
                41, 52, 31, 37, 47, 55,  
                30, 40, 51, 45, 33, 48,  
                44, 49, 39, 56, 34, 53,  
                46, 42, 50, 36, 29, 32] 

# Permute a bit string of length n_bits by given permutation mapping 'pmap'
def perm(bitstr, pmap, n_bits):
    res = ""
    for i in range(0, n_bits):
        res = res + bitstr[pmap[i]-1]
    return res

# Left shift a bit string by given amount
def leftShift(bitstr, amount):
    return bitstr[amount:] + bitstr[0:amount]

##########################################################################################
########################################################################################## 

charToHexStr = {'f': '0000',
                'g': '0001',
                'h': '0010',
                'i': '0011',
                'j': '0100',
                'k': '0101',
                'l': '0110',
                'm': '0111',
                'n': '1000',
                'o': '1001',
                'p': '1010',
                'q': '1011',
                'r': '1100',
                's': '1101',
                't': '1110',
                'u': '1111'}   

charToHexList = { char: [int(x) for x in list(hex)] for char, hex in charToHexStr.items() }

################################################
# Characteristic: 40 08 00 00 04 00 00 00      #
# XOR of input values: 0x0000801000004000      #
################################################

with open('c1.txt') as file:
    ctxt = [line.rstrip() for line in file]


# 0. Hexadecimal of ciphertext

hexCtxt = []
for c in ctxt:
    temp = []
    if len(c) == 16:
        for i in range(16):
            temp.extend(charToHexList[c[i]])
        hexCtxt.extend([temp])


# 1. Reverse of the final permutation

pinv = []
for c in hexCtxt:   
    temp = []
    for i in range(64):
        temp.extend([c[P_rev_final[i]-1]])

    pinv.extend([temp])


# 2. Output XORs

opxor = []
for i in range(0,len(pinv)//2):
    opxor.extend([list(np.bitwise_xor(pinv[2*i], pinv[2*i+1]))])

# 3. Bit expansion of right half from input

rexp = []
for i in range(0, len(pinv)):
    temp = []
    for j in range(48):
        temp.extend([pinv[i][E[j]-1]])

    rexp.extend([temp])

# 4. Inputs to S-box

ipsbox = []
for i in range(0, len(rexp)//2):
    ipsbox.extend([list(np.bitwise_xor(rexp[2*i], rexp[2*i+1]))])

# 5. L5 XOR R6

l5 = [0, 0, 0, 0, 0, 1] + [0 for _ in range(26)]
inxor = []
for i in opxor:
    inxor.extend([list(np.bitwise_xor(i[32:64], l5))])

# 6. Output XOR

opsbox = []
for i in inxor:
    temp = []
    for j in range(32):
        temp.extend([i[IP[j]-1]])
    opsbox.extend([temp])

# 7. Find keys

keys = np.zeros((8, 64))
for i in range(len(ipsbox)):
    if ipsbox[i]:
        for j in range(8):
            ipxor = int(''.join([str(xor) for xor in ipsbox[i][j*6:j*6+6]]), 2)
            opxor = int(''.join([str(xor) for xor in opsbox[i][j*4:j*4+4]]), 2)
            insbox = int(''.join([str(xor) for xor in rexp[2*i+1][j*6:j*6+6]]), 2)
            for k in range(64):
                x = bin(k)[2:].zfill(6)
                y = bin(k ^ ipxor)[2:].zfill(6)
                ax = 2 * int(x[0]) + int(x[5])
                ay = 2 * int(y[0]) + int(y[5])
                bx = 8 * int(x[1]) + 4 * int(x[2]) + 2 * int(x[3]) + int(x[4])
                by = 8 * int(y[1]) + 4 * int(y[2]) + 2 * int(y[3]) + int(y[4])
                if opxor == S[j][ax][bx] ^ S[j][ay][by]:
                    keys[j][k ^ insbox] += 1

mxkey = list()
boxkeys = list()
for i in range(len(keys)):
    mxkey.append(max(keys[i]))
    boxkeys.append(np.where(keys[i] == max(keys[i]))[0][0])

print(f"Keys for first characteristic: \n{boxkeys}")

################################################
# Characteristic: 00 20 00 08 00 00 04 00      #
# XOR of input values: 0x0000080100100000      #
################################################

with open('c2.txt') as file:
    ctxt = [line.rstrip() for line in file]

# 0. Hexadecimal of ciphertext

hexCtxt = []
for c in ctxt:
    temp = []
    if len(c) == 16:
        for i in range(16):
            temp.extend(charToHexList[c[i]])
        hexCtxt.extend([temp])

# 1. Reverse of the final permutation

pinv = []
for c in hexCtxt:   
    temp = []
    for i in range(64):
        temp.extend([c[P_rev_final[i]-1]])

    pinv.extend([temp])


# 2. Output XORs

opxor = []
for i in range(0, len(pinv)-1, 2):
    opxor.extend([list(np.bitwise_xor(pinv[i], pinv[i+1]))])

# 3. Bit expansion of right half from input

rexp = []
for i in range(0, len(pinv)):
    temp = []
    for j in range(48):
        temp.extend([pinv[i][E[j]-1]])

    rexp.extend([temp])

# 4. Inputs to S-box

ipsbox = []
for i in range(0, len(rexp)-1, 2):
    ipsbox.extend([list(np.bitwise_xor(rexp[i], rexp[i+1]))])

# 5. L5 XOR R6

l5 = [0 for _ in range(21)] + [1] + [0 for _ in range(10)]
inxor = []
for i in opxor:
    inxor.extend([list(np.bitwise_xor(i[32:64], l5))])

# 6. Output XOR

opsbox = []
for i in inxor:
    temp = []
    for j in range(32):
        temp.extend([i[IP[j]-1]])
    opsbox.extend([temp])

# 7. Find keys

keys = np.zeros((8, 64))
for i in range(len(ipsbox)):
    if ipsbox[i]:
        for j in range(8):
            ipxor = int(''.join([str(xor) for xor in ipsbox[i][j*6:j*6+6]]), 2)
            opxor = int(''.join([str(xor) for xor in opsbox[i][j*4:j*4+4]]), 2)
            insbox = int(''.join([str(xor) for xor in rexp[2*i+1][j*6:j*6+6]]), 2)
            for k in range(64):
                x = bin(k)[2:].zfill(6)
                y = bin(k ^ ipxor)[2:].zfill(6)
                ax = 2 * int(x[0]) + int(x[5])
                ay = 2 * int(y[0]) + int(y[5])
                bx = 8 * int(x[1]) + 4 * int(x[2]) + 2 * int(x[3]) + int(x[4])
                by = 8 * int(y[1]) + 4 * int(y[2]) + 2 * int(y[3]) + int(y[4])
                if opxor == S[j][ax][bx] ^ S[j][ay][by]:
                    keys[j][k ^ insbox] += 1

mxkey = list()
boxkeys = list()
for i in range(len(keys)):
    mxkey.append(max(keys[i]))
    boxkeys.append(np.where(keys[i] == max(keys[i]))[0][0])

print(f"Keys for second characteristic: \n{boxkeys}")