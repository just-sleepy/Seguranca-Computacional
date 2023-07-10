from RSA import generateKey
from OAEP import oaepEncr, oaepDecr
import AES
from AES import split_blocks
import signaturefile

message = b"Num ninho de mafagafos ha sete mafagafinhos. Quando a mafagafa gafa, gafam os sete mafagafinhos."
print("Original message:", message)

########## PARTE 1 ##########
# geracao de chave de 128 bits
# cifracao e decifracao

aes = AES.AES()

blocos_cipher = [aes.cipher(block) for block in split_blocks(message)]
blocos_decipher = [aes.decipher(block) for block in blocos_cipher]

aes_cif = aes.cipher(message)
aes_dec = aes.decipher(aes_cif)

print()
print("AES key:", aes.key)
print("AES ciphertext", blocos_cipher)
print("AES decrypted message:", blocos_decipher)
print()

########## PARTE 2 ##########
# geracao de chave do RSA testando primalidade com Miller-Rabin
# cifracao e decifracao assimetrica RSA utilizando OAEP

private_key, public_key = generateKey()
ciphertext = oaepEncr(message, public_key)
decrypted_message = oaepDecr(ciphertext, private_key)
print()
print("RSA private key:", private_key)
print("RSA public key: ", public_key)
print("RSA ciphertext:", ciphertext)
print("RSA decrypted message:", decrypted_message)
print()

########## PARTE 3 ##########
# assinatura da mensagem
# formatacao com base64

signature = signaturefile.signMessage(message, private_key)

print()
print("RSA signature: ", signature)
print()

########## PARTE 4 ##########
# verificacao

signature_flag = signaturefile.verifySignature(message, signature, public_key)
if signature_flag:
    print("Valid signature")
else:
    print("Invalid signature")

#############################