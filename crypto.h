#include "DES.h"
#include "AES.h"
#include <string>
#include <array>
#include <cstdint>
#include <vector>

using std::vector, std::array;

namespace crypto{

class AES{
public:
    AES(const array<unsigned char, 16> &key):cryptor(128), key(key){cryptor.KeyExpansion(key.data(), subKey.data());}
    array<unsigned char, 16> encrypt(const array<unsigned char, 16> &plaintext){
        array<unsigned char, 16> out;
        cryptor.EncryptBlock(plaintext.data(), out.data(), subKey.data());
        return out;
    }
    array<unsigned char, 16> decrypt(const array<unsigned char, 16> &ciphertext){
        array<unsigned char, 16> out;
        cryptor.DecryptBlock(ciphertext.data(), out.data(), subKey.data());
        return out;
    }
private:
    AesBasic cryptor;
    array<unsigned char, 16> key;
    array<unsigned char, 4*4*11> subKey;
};

class DES{
public:
    DES(const array<unsigned char, 8> &key);
    array<unsigned char, 8> encrypt(const array<unsigned char, 8> &plaintext);
    array<unsigned char, 8> decrypt(const array<unsigned char, 8> &ciphertext);
    uint64_t charArrayToint64(const array<unsigned char, 8> &msg);
    array<unsigned char, 8> int64TocharArray(uint64_t msg);
private:
    DesBasic cryptor;
    uint64_t key;
    array<uint64_t, 16> subKey;
};

} // namespace crypto
