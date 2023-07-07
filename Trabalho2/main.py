from AES import AES, split_blocks, padding

aes = AES()

mensagem = bytes("teste mensagem".encode())
mensagem = padding(mensagem)

# chave de 16 bytes
key = bytes("teste chave".encode())
blocos_cipher = []

for msg_block in split_blocks(mensagem):
    blocos_cipher.append(aes.cipher(msg_block, key))

blocos_decipher = []
for block in blocos_cipher:
    blocos_decipher.append(aes.decipher(block, key))

print(blocos_cipher)
print(blocos_decipher)
