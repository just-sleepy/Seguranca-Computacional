from AES import AES, split_blocks, padding
from keys import generate_key

# aes = AES(bytes("teste123".encode()))
aes = AES()

mensagem = padding(bytes("mensagem a ser cifrada".encode()))

blocos_cipher = [aes.cipher(block) for block in split_blocks(mensagem)]
blocos_decipher = [aes.decipher(block) for block in blocos_cipher]

print(blocos_cipher)
print(blocos_decipher)
