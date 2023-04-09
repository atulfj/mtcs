import numpy as np 
import galois
from pyfinite import ffield

F = ffield.FField(7, gen=0x83)
G = galois.GF(128)
f = ord('f')

def exponent(b, exp):
	res = b
	for i in range(1, exp):
		res = F.Multiply(res, b)
	return res

def linear_transform(mat, msg):
	res = [0 for _ in range(8)]
	for i in range(8):
		xor = []
		prod = [F.Multiply(mat[i][j], msg[i]) for j in range(8)]
		for j in range(8):
			xor.append(np.bitwise_xor(res[j], prod[j]))
		res = xor 
	return res

def read(ctxt):
	res = ""
	clen = len(ctxt)
	for i in range(0, clen, 2):
		temp = ctxt[i: i+2]
		res += chr(16 * (ord(temp[0]) - f) + ord(temp[1]) - f)
	return res

def eaeae(msgs, mat, pow_mat):
	msgs = [ord(msg) for msg in msgs]
	res = [exponent(msgs[i], pow_mat[i]) for i in range(8)]
	res = linear_transform(mat, res)
	res = [exponent(res[i], pow_mat[i]) for i in range(8)]
	res = linear_transform(mat, res)
	res = [exponent(res[i], pow_mat[i]) for i in range(8)]
	return res

def get_einv(blk, einv, e):
	return [einv[e[i]][blk[i]] for i in range(8)]

def get_ainv(blk, a):
	return np.matmul(G(a), G(blk))
