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

class AES_CBC {
    public:
        AES_CBC(const array<unsigned char, 16> &key) :cryptor(128), key(key) {

            //random generate initVec

            for (int i = 0; i < 4; i++) {
                int tmp = rand();
                initVec[i*4 + 0] = (unsigned char)tmp;
                initVec[i*4 + 1] = (unsigned char)tmp >> 8;
                initVec[i*4 + 2] = (unsigned char)tmp >> 16;
                initVec[i*4 + 3] = (unsigned char)tmp >> 24;
            }

            cryptor.KeyExpansion(key.data(), subKey.data());
        }

        vector<unsigned char> encrypt(const vector<unsigned char> &plaintext) {
            int length = plaintext.size();
            int rounds = (length % 16 == 0 ? length / 16 : length/16+1);
            bool first_round = true;
            int start = 0;
            int end = 0;
            unsigned char input[16] = {0};
            unsigned char _ciphertext[16] = {0};
            unsigned char _plaintext[16] = {0};
            vector<unsigned char> out;

            for (int round_idx = 0; round_idx < rounds; round_idx++) {
                start = round_idx * 16;
                end = (round_idx + 1) * 16;

                if (end > length) {
                    end = length;
                }

                memset(_plaintext, 0, 16);
                memcpy(_plaintext, plaintext.data()+start, end-start);

                memset(input, 0, 16);
                for (int i = 0; i < 16; i++) {
                    if (first_round) {
                        input[i] = _plaintext[i] ^ initVec[i];
                    }else {
                        input[i] = _plaintext[i] ^ _ciphertext[i];
                    }
                }

                first_round = false;

                cryptor.EncryptBlock(input, _ciphertext, subKey.data());

                for (int i = 0; i < end-start; i++){
                    out.push_back(_ciphertext[i]);
                }
            }

            return out;
        }

        vector<unsigned char> decrypt (const vector<unsigned char> &ciphertext) {
            int length = ciphertext.size();
            int rounds = (length%16 == 0 ? length/16 : length/16+1);
            bool first_round = true;
            int start = 0;
            int end = 0;
            unsigned char output[16] = {0};
            unsigned char input[16] = {0};
            unsigned char _ciphertext[16] = {0};
            unsigned char _plaintext[16] = {0};

            vector<unsigned char> out;

            for (int roundIdx = 0; roundIdx < rounds; roundIdx ++) {
                start = roundIdx * 16;
                end = (roundIdx+1) * 16;
                if (end > length)
                    end = length;
                memset(_ciphertext, 0, 16);
                memcpy(_ciphertext, ciphertext.data()+start, end-start);
                cryptor.DecryptBlock(_ciphertext, output, subKey.data());
                for (int i = 0; i < 16; i++) {
                    if (first_round) {
                        _plaintext[i] = output[i] ^ initVec[i];
                    }else {
                        _plaintext[i] = output[i] ^ input[i];
                    }
                }
                first_round = false;

                for (int i = 0; i < end-start; i++) {
                    out.push_back(_plaintext[i]);
                }

                memcpy(input, _ciphertext, end-start);
            }

            return out;
        }

    private:
        AesBasic cryptor;
        //initVec is used to encrypt the first group plaintext
        unsigned char initVec[16];
        array<unsigned char, 16> key;
        array<unsigned char, 4*4*11> subKey;
};

class AES_ECB {
public:
    AES_ECB(const array<unsigned char, 16> &key): crypotor(128), key(key) {
         crypotor.KeyExpansion(key.data(), subKey.data());
    }

    vector <unsigned char> encrypt(const vector<unsigned char> &plaintext) {
        int length = plaintext.size();
        int rounds = (length % 16 == 0 ? length/16 : length/16+1);
        int start = 0;
        int end = 0;

        unsigned char _ciphertext[16] = {0};
        unsigned char _plaintext[16] = {0};

        vector<unsigned char> out;

        for (int round_idx = 0; round_idx < rounds; ++round_idx) {
            start = round_idx * 16;
            end = (round_idx + 1) * 16;
            if (end > length)
                end = length;

            memset(_ciphertext, 0 , 16) ;
            memset(_plaintext, 0, 16);
            memcpy(_plaintext, plaintext.data()+start, end-start);

            crypotor.EncryptBlock(_plaintext, _ciphertext, subKey.data());

            for (int i = 0; i < end - start; ++i) {
                out.push_back(_ciphertext[i]);
            }
        }

        return out;

    }

    vector <unsigned char> decrypt(const vector<unsigned char> &ciphertext) {
        int length = ciphertext.size();
        int rounds = (length % 16 == 0 ? length/16: length/16+1);
        int start = 0;
        int end = 0;

        unsigned char _ciphertext[16] = {0};
        unsigned char _plaintext[16] = {0};

        vector <unsigned char> out;

        for (int round_idx = 0; round_idx < rounds; ++round_idx) {
            start = round_idx * 16;
            end = (round_idx + 1) * 16;
            if (end > length)
                end = length;

            memset(_ciphertext, 0, 16);
            memset(_plaintext, 0, 16);
            memcpy(_ciphertext, ciphertext.data()+start, end-start);
            crypotor.DecryptBlock(_ciphertext, _plaintext, subKey.data());

            for (int i = 0; i < end - start; ++i) {
                out.push_back(_plaintext[i]);
            }
        }

        return out;

    }

private:
    AesBasic crypotor;
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
