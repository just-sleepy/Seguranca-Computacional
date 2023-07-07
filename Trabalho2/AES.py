from utils import s_box, inv_s_box, rcon

def convert(msg, size):
    lista = []
    for idx in range(0, len(msg), size):
        lista.append(msg[idx: idx + size])

    return lista

def rotate(list):
    return (list*2)[1:5]

def inc_bytes(a):
    out = list(a)
    for i in reversed(range(len(out))):
        if out[i] == 0xFF:
            out[i] = 0
        else:
            out[i] += 1
            break
    return bytes(out)

def xor_bytes(a, b):
    """ Returns a new byte array with the elements xor'ed. """
    return bytes(i^j for i, j in zip(a, b))

def bytes2matrix(text):
    """ Converts a 16-byte array into a 4x4 matrix.  """
    return [list(text[i:i+4]) for i in range(0, len(text), 4)]

def matrix2bytes(matrix):
    """ Converts a 4x4 matrix into a 16-byte array.  """
    return bytes(sum(matrix, []))

xtime = lambda a: (((a << 1) ^ 0x1B) & 0xFF) if (a & 0x80) else (a << 1)

def padding(msg):
    padding_len = 16 - (len(msg) % 16)
    padd = bytes([padding_len] * padding_len)
    return bytes(msg + padd)

def split_blocks(msg, size=16):
    return [msg[i:i+16] for i in range(0, len(msg), size)]

class AES:
    def __init__(self):
        self.n_rounds = 10
    def cipher(self, msg, key):
        keys = self.expand_key(key)
        blocks = bytes2matrix(msg)

        mat = self.add_round_key(blocks, keys[0])

        for round in range(1, self.n_rounds):
            mat = self.subBytes(mat)
            mat = self.shiftRows(mat)
            mat = self.mix_columns(mat)
            mat = self.add_round_key(mat, keys[round])
                
        mat = self.subBytes(mat)
        mat = self.shiftRows(mat)
        mat = self.add_round_key(mat, keys[-1])

        return matrix2bytes(mat)

    def decipher(self, msg, key):
        keys = self.expand_key(key)
        blocks = bytes2matrix(msg)

        mat = self.add_round_key(blocks, keys[-1])
        mat = self.inv_shiftRows(mat)
        mat = self.inv_subBytes(mat)
        for round in range(self.n_rounds-1, 0, -1):
            mat = self.add_round_key(mat, keys[round])
            mat = self.inv_mix_columns(mat)
            mat = self.inv_shiftRows(mat)
            mat = self.inv_subBytes(mat)

        mat = self.add_round_key(blocks, keys[0])
        return matrix2bytes(mat)
    
    def expand_key(self, key):
        key_columns = bytes2matrix(key)
        iteration_size = len(key) // 4

        i = 1
        while len(key_columns) < (self.n_rounds + 1) * 4:
            # Copy previous word.
            word = list(key_columns[-1])

            # Perform schedule_core once every "row".
            if len(key_columns) % iteration_size == 0:
                # Circular shift.
                word.append(word.pop(0))
                # Map to S-BOX.
                word = [s_box[b] for b in word]
                # XOR with first byte of R-CON, since the others bytes of R-CON are 0.
                word[0] ^= rcon[i]
                i += 1

            # XOR with equivalent word from previous iteration.
            word = xor_bytes(word, key_columns[-iteration_size])
            key_columns.append(word)

        # Group key words in 4x4 byte matrices.
        return [key_columns[4*i : 4*(i+1)] for i in range(len(key_columns) // 4)]

    def subBytes(self, mat):
        for i in range(4):
            for j in range(4):
                mat[i][j] = s_box[mat[i][j]]
        return mat

    def shiftRows(self, mat):

        mat[0][1], mat[1][1], mat[2][1], mat[3][1] = mat[1][1], mat[2][1], mat[3][1], mat[0][1]
        mat[0][2], mat[1][2], mat[2][2], mat[3][2] = mat[2][2], mat[3][2], mat[0][2], mat[1][2]
        mat[0][3], mat[1][3], mat[2][3], mat[3][3] = mat[3][3], mat[0][3], mat[1][3], mat[2][3]
        return mat
        # 1 shift, 2 shift, 3 shift

    def mix_column(self, mat):
        t = mat[0]^mat[1]^mat[2]^mat[3]
        u = mat[0]
        mat[0] ^= t ^ xtime(mat[0] ^ mat[1])
        mat[1] ^= t ^ xtime(mat[1] ^ mat[2])
        mat[2] ^= t ^ xtime(mat[2] ^ mat[3])
        mat[3] ^= t ^ xtime(mat[3] ^ u)
        return mat
    
    # inverses
    def inv_subBytes(self, mat):
        for i in range(4):
            for j in range(4):
                mat[i][j] = inv_s_box[mat[i][j]]
        return mat
    
    def inv_shiftRows(self, mat):
        mat[0][1], mat[1][1], mat[2][1], mat[3][1] = mat[3][1], mat[0][1], mat[1][1], mat[2][1]
        mat[0][2], mat[1][2], mat[2][2], mat[3][2] = mat[2][2], mat[3][2], mat[0][2], mat[1][2]
        mat[0][3], mat[1][3], mat[2][3], mat[3][3] = mat[1][3], mat[2][3], mat[3][3], mat[0][3]
        return mat
    
    def mix_columns(self, mat):
        for i in range(4):
            mat[i] = self.mix_column(mat[i])
        return mat
    
    def inv_mix_columns(self, mat):
        for i in range(4):
            u = xtime(xtime(mat[i][0] ^ mat[i][2]))
            v = xtime(xtime(mat[i][1] ^ mat[i][3]))
            for j in range(4):
                mat[i][j] ^= (u if j%2==0 else v)
        mat = self.mix_columns(mat)
        return mat
                
    def add_round_key(self, mat, key):
        for i in range(4):
            for j in range(4):
                mat[i][j] ^= key[i][j]
        return mat