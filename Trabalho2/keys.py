import random

def generate_key():
    return [random.randint(0, 0xff) for _ in range(16)]