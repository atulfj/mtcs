from utils import *

exps = [[] for _ in range(8)]
diags = [[[] for _ in range(8)] for _ in range(8)]

fp = open('p.txt', 'r')
ptxt = fp.readlines()[0].strip().split(' ')

fc = open('c.txt', 'r')
ctxt = fc.readlines()

ip = [read(p)[0] for p in ptxt]
op = [[read(c)[i] for c in ctxt[i].strip().split(' ')] for i in range(len(ctxt))]

for i in range(8):
	for j in range(1, 127):
		for k in range(1, 128):
			found = True
			for l in range(128):
				x = exponent(ord(ip[l]), j)
				x = F.Multiply(x, k)
				x = exponent(x, j)
				x = F.Multiply(x, k)
				x = exponent(x, j)
				y = ord(op[i][l])
				if x != y:
					found = False
					break
			if found:
				exps[i].append(j)
				diags[i][i].append(k)
				
print(f"Possible diagonal values: \n{diags}\n\nPossible exponent values: \n{exps}\n\n")

op = [[read(c)[i+1] for c in ctxt[i].strip().split(' ')] for i in range(len(ctxt)-1)]

for i in range(7):
	for j in range(1, 128):
		for e1, d1 in zip(exps[i+1], diags[i+1][i+1]):
			for e2, d2 in zip(exps[i], diags[i][i]):
				for k in range(128):
					found = True
					x1 = exponent(ord(ip[k]), e2)
					x1 = F.Multiply(x1, d2)
					x1 = exponent(x1, e2)
					x1 = F.Multiply(x1, j)
					x2 = exponent(ord(ip[k]), e2)
					x2 = F.Multiply(x2, j)
					x2 = exponent(x2, e1)
					x2 = F.Multiply(x2, d1)
					xor = np.bitwise_xor(x1, x2)
					y = ord(op[i][k])
					if exponent(xor, e1) != y:
						found = False
						break
				if found:
					exps[i] = [e2]
					exps[i+1] = [e1]
					diags[i][i] = [d2]
					diags[i][i+1] = [j]
					diags[i+1][i+1] = [d1]

fp = open('p.txt', 'r')
fc = open('c.txt', 'r')
ptxt = fp.readlines()
ctxt = fc.readlines()
ip = [[read(p) for p in ptxt[i].strip().split(' ')] for i in range(len(ptxt))]
op = [[read(c) for c in ctxt[i].strip().split(' ')] for i in range(len(ctxt))]

for idx in range(6):
	c = idx+2
	explst = [exp[0] for exp in exps]
	mat = np.zeros((8, 8), dtype=np.int32)
	for i in range(8):
		for j in range(8):
			if len(diags[i][j]):
				mat[i][j] = diags[i][j][0]
			else:
				mat[i][j] = 0
	for i in range(8):
		if i > 7-c:
			continue
		else:
			for j in range(127):
				mat[i][i+c] = j+1
				found = True
				for a, b in zip(ip[i], op[i]):
					x = eaeae(a, mat, explst)[i+c]
					y = ord(b[i+c])
					if x != y:
						found = False
						break
				if found:
					diags[i][i+c] = [j+1]

A = np.zeros((8, 8), dtype=np.int32)
E = explst

for i in range(8):
	for j in range(8):
		if len(diags[j][i]):
			A[i][j] = diags[j][i][0]

print(f"A: \n{A}\n\nE: \n{E}\n\n")

Ainv = np.linalg.inv(G(A))
Einv = np.zeros((128, 128), dtype=np.int32)
for b in range(128):
	res = 1
	for exp in range(1, 127):
		temp = F.Multiply(res, b)
		Einv[exp][temp] = b
		res = temp

print(f"Inverse of A: \n{Ainv}\n\nInverse of E: \n{Einv}\n\n")

###########################
# DECRYPTING THE PASSWORD #
###########################

pwd_cipher = "mshjhijnlslffmkrlofpmofsfslkfqgl"
pwd = ""
for i in range(2):
	p = pwd_cipher[16*i:16*(i+1)]
	temp = []
	for j in range(0, 15, 2):
		temp += [(ord(p[j])-f)*16 + (ord(p[j+1])-f)]
	pwd_bytes = get_einv(temp, Einv, E)
	pwd_bytes = get_ainv(pwd_bytes, Ainv)
	pwd_bytes = get_einv(pwd_bytes, Einv, E)
	pwd_bytes = get_ainv(pwd_bytes, Ainv)
	pwd_bytes = get_einv(pwd_bytes, Einv, E)
	for byte in pwd_bytes:
		pwd += chr(byte)

print(f"~~~~~~~~~~LEVEL 5 PASSWORD~~~~~~~~~~\n{pwd}")
