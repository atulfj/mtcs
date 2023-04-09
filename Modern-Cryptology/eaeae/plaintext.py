def genPtxt(chars, r):
    p = []
    ff = 'ff'
    for i in range(8):
        for j in range(16):
            p.append(ff*r + chars[i] + chars[j] + ff*(8-1-r))
    return p

chars = ['f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u']
ptxt = [genPtxt(chars, r) for r in range(8)]

f = open("p.txt", "w")
for p in ptxt:
    f.write(' '.join(p) + '\n')
f.close()
