from RSA import encRsa, decRsa
from OAEP import sha3_256
import base64

def signMessage(message, private_key):
    hash_message = sha3_256(message)
    encrypted_hash = encRsa(int.from_bytes(hash_message, byteorder='big'), private_key)

    # formata o resultado em BASE64
    encoded_result = base64.b64encode(encrypted_hash.to_bytes((encrypted_hash.bit_length() + 7) // 8, byteorder='big'))
    return encoded_result

def verifySignature(message, signature, public_key):
    # decodifica o resultado em BASE64
    decoded_signature = int.from_bytes(base64.b64decode(signature), byteorder='big')

    # descriptografa a assinatura usando RSA
    decrypted_signature = decRsa(decoded_signature, public_key)
    hash_message = sha3_256(message)

    # verifica se a assinatura corresponde ao hash
    if decrypted_signature == int.from_bytes(hash_message, byteorder='big'):
        return True
    else:
        return False