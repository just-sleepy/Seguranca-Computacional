import random
BLOCK_SIZE = 128

def generate_key():
    key = []
    n = random.randint(0, 0xffffffffffffffffffffffffffffffff)
    for i in range(int(BLOCK_SIZE/8)):
        key.append(n&0xff)
        n >>= 8

    return key