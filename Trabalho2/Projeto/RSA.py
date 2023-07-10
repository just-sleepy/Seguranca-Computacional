import random
import math

#gera primo de n bits
def primeGenerator(n):
    while(True):
        x = random.randrange(1 << (n-1), (1 << n) - 1)
        if(millerRabin(x)):
            return x

#teste probabilístico da primitividade de n
def millerRabin(n, rounds = 45):
    cnt = 0
    k = n - 1
    while(k % 2 == 0):
        cnt += 1
        k >>= 1
    for i in range(rounds):
        x = pow(random.randrange(2, n-1), k, n)
        if(x == 1 or x == n-1):
            continue
        flag = False
        for j in range(cnt - 1):
            x = (x * x) % n
            if(x == n - 1):
                flag = True
        if(flag == False):
            return False
    return True


def modularInverse(a, m):
    x1, x2, x3 = 1, 0, a
    y1, y2, y3 = 0, 1, m
    while y3 != 0:
        q = x3 // y3
        y1, x1 = (x1 - q * y1), y1
        y2, x2 = (x2 - q * y2), y2
        y3, x3 = (x3 - q * y3), y3
    return x1 % m
    

def generateKey():
    #garante que p e q primos e p != q
    p = primeGenerator(1024)
    q = primeGenerator(1024)
    while(p == q):
        q = primeGenerator(1024)
    #gera chave do RSA, utilizando inverso modular
    n = p * q
    n2 = (p-1) * (q-1)
    e = random.randrange(2, n2)
    while(math.gcd(e, n2) != 1):
        e = random.randrange(2, n2)
    d = modularInverse(e, n2)
    priv_key = (d, n)
    publ_key = (e, n)
    return priv_key, publ_key

def encRsa(msg, publ_key):
    e = publ_key[0]
    n = publ_key[1]
    return pow(msg, e, n)

def decRsa(msg, priv_key):
    d = priv_key[0]
    n = priv_key[1]
    return pow(msg, d, n)