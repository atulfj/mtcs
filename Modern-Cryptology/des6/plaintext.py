import numpy as np

# Hexadecimal form of characters -> characters
hexToChar = {'0000': 'f',
            '0001': 'g',
            '0010': 'h',
            '0011': 'i',
            '0100': 'j',
            '0101': 'k',
            '0110': 'l',
            '0111': 'm',
            '1000': 'n',
            '1001': 'o',
            '1010': 'p',
            '1011': 'q',
            '1100': 'r',
            '1101': 's',
            '1110': 't',
            '1111': 'u'    
            }

# Reverse mapping of above
charToHex = { char: hex for hex, char in hexToChar.items() }

bits = 64 
nPtxt = 5000

################################################
# Characteristic: 40 08 00 00 04 00 00 00      #
# XOR of input values: 0x0000801000004000      #
################################################

xorHex = 0x0000801000004000
xor = [int(x) for x in str((bin(xorHex))[2:].zfill(bits))]

ptxtBin = list()
for i in range(nPtxt):
    curstr = np.random.choice(a=[tup[1] for tup in hexToChar.items()], size=(1, 16))[0]
    binary = list()
    for char in curstr:
        binary += [int(hex) for hex in charToHex[char]]
    
    ptxtBin.append(binary)
    ptxtBin.append(list(np.bitwise_xor(binary, xor)))

ptxt = list()
for i in range(len(ptxtBin)):
    curstr = ""
    for j in range(0, bits, 4):
        curstr += hexToChar[''.join([str(x) for x in ptxtBin[i][j:j+4]])]
    ptxt += [curstr]

# Write plaintexts into a file
f = open("p1.txt", "w")
for elem in ptxt:
    f.write(elem + '\n')
f.close()

################################################
# Characteristic: 00 20 00 08 00 00 04 00      #
# XOR of input values: 0x0000080100100000      #
################################################

xorHex = 0x0000080100100000
xor = [int(x) for x in str((bin(xorHex))[2:].zfill(bits))]

ptxtBin = list()

for i in range(nPtxt):
    curstr = np.random.choice(a=[tup[1] for tup in hexToChar.items()], size=(1, 16))[0]
    binary = list()
    for char in curstr:
        binary += [int(hex) for hex in charToHex[char]]
    
    ptxtBin.append(binary)
    ptxtBin.append(list(np.bitwise_xor(binary, xor)))

ptxt = list()
for i in range(len(ptxtBin)):
    curstr = ""
    for j in range(0, bits, 4):
        curstr += hexToChar[''.join([str(x) for x in ptxtBin[i][j:j+4]])]
    ptxt += [curstr]

# Write plaintexts into a file
f = open("p2.txt", "w")
for elem in ptxt:
    f.write(elem + '\n')
f.close()