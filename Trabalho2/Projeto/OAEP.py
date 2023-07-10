# Referência: https://akasatanahama.com/posts/304/

import hashlib
import os
import RSA

def sha3_256(m):
    sha3 = hashlib.sha3_256()
    sha3.update(m)
    return sha3.digest()

def mgf1(seed, mlen):
    t = b''
    hlen = 32 #tamanho da sha3_256
    val = (mlen // hlen) + ((mlen % hlen) != 0) #teto
    for i in range(0, val):
        aux_i = i.to_bytes(4, byteorder='big')
        t += sha3_256(seed + aux_i)
    return t[:mlen]

def xor(x: bytes, y: bytes) -> bytes:
    return bytes(a ^ b for a, b in zip(x, y))

def oaepEncr(m, publ_key):
    k = publ_key[1].bit_length() // 8
    return RSA.encRsa(int.from_bytes(oaepEncode(m, k), byteorder='big'), publ_key)

def oaepEncode(m, k, label = b'', mgf1 = mgf1) -> bytes:
    mlen = len(m)
    lhash = sha3_256(label)
    hlen = len(lhash)

    ps = b'\x00' * (k - mlen - 2 * hlen - 2)
    db = lhash + ps + b'\x01' + m
    seed = os.urandom(hlen)

    db_mask = mgf1(seed, k - hlen - 1)
    masked_db = xor(db, db_mask)

    seed_mask = mgf1(masked_db, hlen)
    masked_seed = xor(seed, seed_mask)

    return b'\x00' + masked_seed + masked_db

def oaepDecr(c, private_key):
        k = private_key[1].bit_length() // 8
        return oaepDecode(RSA.decRsa(c, private_key).to_bytes(k, byteorder='big'), k)

def oaepDecode(c: bytes, k: int, label: bytes = b'', sha3_256 = sha3_256) -> bytes:
    lhash = sha3_256(label)
    hlen = len(lhash)
    masked_seed, masked_db = c[1:1 + hlen], c[1 + hlen:]

    seed_mask = mgf1(masked_db, hlen)
    seed = xor(masked_seed, seed_mask)

    db_mask = mgf1(seed, k - hlen - 1)
    db = xor(masked_db, db_mask)
    i = hlen

    while i < len(db):
        if db[i] == 1:
            i += 1
            break
        i += 1
    m = db[i:]
    return m