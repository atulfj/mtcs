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

password = "mqlllnqimkprslurqinupgquulmqfghg"

# "2 letters for one"
pairValues = []
for i in range(0, len(password), 2):
    pairValues.append(int(charToHexStr[password[i]] + charToHexStr[password[i+1]], 2))

print(pairValues)
