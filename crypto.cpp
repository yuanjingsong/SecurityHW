#include "crypto.h"
#include <stdio.h>

namespace crypto{

DES::DES(const array<unsigned char, 8> &key){
    this->key = charArrayToint64(key);
    subKey = this->cryptor.initSubKey(this->key);
}

uint64_t DES::charArrayToint64(const array<unsigned char, 8> &msg){
    int shift_size = 56;
    uint64_t v = 0;
    for(int i=0; i < 8; ++i){
        v |= uint64_t(msg[i]) << shift_size;
        shift_size -= 8;
    }
    return v;
}

array<unsigned char, 8> DES::int64TocharArray(uint64_t msg){
    array<unsigned char, 8> res;
    uint64_t mask = 0xFF00000000000000;
    int shift_size = 56;
    for(int i=0; i < 8; ++i){
        res[i] = (unsigned char)((msg & mask) >> shift_size);
        mask = mask >> 8;
        shift_size -= 8;
    }
    return res;
}

array<unsigned char, 8> DES::encrypt(const array<unsigned char, 8> &plaintext){
    uint64_t msg = this->charArrayToint64(plaintext);
    //printf ("E: %016llx\n", msg);
    msg = this->cryptor.encrypt(msg, subKey);
    return int64TocharArray(msg);
}

array<unsigned char, 8> DES::decrypt(const array<unsigned char, 8> &ciphertext){
    uint64_t msg = this->charArrayToint64(ciphertext);
    //printf ("D: %016llx\n", msg);
    msg = this->cryptor.decrypt(msg, subKey);
    return int64TocharArray(msg);
}

} // namespace crypto
