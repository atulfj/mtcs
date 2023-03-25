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

# Generate a round-key for the given key and round
def generateRoundKey(key, round):
    l = key[0:28]
    r = key[28:56]
    roundKey = []
    for i in range(round):
        l = leftShift(l, shifts[i])
        r = leftShift(r, shifts[i])
        key = l + r
        roundKey.extend([perm(key, key_compress, 48)])
    return roundKey

# DES encryption for given input (ip), key (key) and rounds (n_rounds)
def desbad(ip, key, n_rounds):
    # 1. Initial permutation
    ip = perm(ip, P_initial, 64)
    # 2. Separate left and right halves
    l = ip[:32]
    r = ip[32:]
    # 3. Perform rounds
    for i in range(n_rounds):
        # 4. Bit expansion
        E_ip = perm(r, E, 48)
        # 5. XOR with key
        key_xor_ip = str(bin(np.bitwise_xor(int(E_ip, 2), int(key[i], 2)))[2:])
        if len(key_xor_ip) != 48:
            key_xor_ip += ('0' * (48 - len(key_xor_ip)))
        # 6. S-box output
        sbox_op = ""
        for j in range(8):
            aux = (bin(S[j][int(key_xor_ip[j*6] + key_xor_ip[j*6+5], 2)][int(key_xor_ip[j*6+1:j*6+5], 2)])[2:])
            sbox_op += aux + ('0' * (4 - len(aux)))
        sbox_op = perm(sbox_op, P_sbox, 32)
        # 7. Final XOR
        xor = str(bin(np.bitwise_xor(int(l, 2), int(sbox_op, 2)))[2:])
        # Padding if output isn't 32 bits
        if len(xor) != 32:
            xor += ('0' * (32 - len(xor)))
        l = xor 
        # Swap
        if i != n_rounds-1:
            aux = l
            l = r
            r = aux 
        op = l + r
        # 8. Return after final permutation
        return perm(op, P_final, 64) 
    

def des_forward(ip, key, n_rounds):
    # 1. Initial permutation
    ip = perm(ip, P_initial, 64)
    # 2. Left and right halves
    l = ip[:32]
    r = ip[32:]
    # 3. Perform round operations
    for i in range(n_rounds):
        # 4. Bit expansion
        e_ip = perm(r, E, 48)
        # 5. XOR with key
        key_xor_ip = str(bin(np.bitwise_xor(int(e_ip, 2), int(key[i], 2)))[2:])
        if len(key_xor_ip)!= 48:
            key_xor_ip = ('0' * (48-len(key_xor_ip))) + key_xor_ip
        # 6. S-box operations
        s_out = ''
        for j in range(8):
            aux = (bin(S[j][int(key_xor_ip[j*6] + key_xor_ip[j*6+5], 2)][int(key_xor_ip[j*6+1:j*6+5], 2)])[2:])
            s_out+= ('0' * (4-len(aux)) + aux)
        s_out = perm(s_out, P_sbox, 32)
        # 7. Final XOR
        xor = str(bin(np.bitwise_xor(int(l, 2), int(s_out, 2)))[2:])
        if len(xor) != 32:
            xor= ('0' * (32-len(xor))) + xor
        l = xor

        if i != n_rounds-1:
            t = l
            l = r
            r = t

    
    op = l + r
    return perm(op, P_final, 64)

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

# The following key is obtained after running findkey1.py

rawKey = "x11xx1xx01011x100xx11x11100x0111001x11011001x11x0111x001"

# Take a plaintext and ciphertext pair from p1.txt and c1. txt to find round-keys
ptxt, ctxt = "", ""
with open('p1.txt') as file:
    line = file.readline().strip('\n')
    for char in line:
        ptxt += charToHexStr[char]
print(f"Chosen plaintext: \n{ptxt}")

with open('c1.txt') as file:
    line = file.readline().strip('\n')
    for char in line:
        ctxt += charToHexStr[char]
print(f"Corresponding ciphertext: \n{ctxt}")

# Brute force to find all possible 14-bit strings
all14 = [] # all 14-bit strings
for i in range(2**14):
    bitstr = str(bin(i)[2:])
    all14.append(('0') * (14-len(bitstr)) + bitstr) # padding

candidates = [] # candidates for actual 56-bit key
for bitstr in all14:
    curKey = list(rawKey)
    cur = 0
    # Place the bits in missing places of 42-bit key
    for j in range(len(curKey)):
        if curKey[j] == 'x':
            curKey[j] = bitstr[cur]
            cur += 1
    candidates.append(''.join(curKey))

key = "" # actual 56 bits key

for candidate in candidates:
    c = generateRoundKey(candidate, 6)
    if des_forward(ptxt, c, 6) == ctxt:
        key = candidate

print(f"The key is: \n{key}")
