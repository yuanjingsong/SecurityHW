#ifndef DES_H
#define DES_H

#include <cstdint>
#include <array>

using std::array;

class DesBasic{
public:
    DesBasic():LB32_MASK(0x00000001), LB64_MASK(0x0000000000000001), L64_MASK(0x00000000ffffffff), H64_MASK(0xffffffff00000000), ISDECRYPT(1), ISENCRYPT(0){}
    array<uint64_t, 16> initSubKey(uint64_t key);
    uint64_t encrypt(uint64_t msg,  const array<uint64_t, 16> &sub_key){return f_function(msg, sub_key, ISENCRYPT);}
    uint64_t decrypt(uint64_t msg,  const array<uint64_t, 16> &sub_key){return f_function(msg, sub_key, ISDECRYPT);}
private:
    uint64_t f_function(uint64_t msg, const array<uint64_t, 16> &sub_key, int mode);
    const uint32_t LB32_MASK;
    const uint64_t LB64_MASK;
    const uint64_t L64_MASK;
    const uint64_t H64_MASK;
    const int ISDECRYPT;
    const int ISENCRYPT;
    static array<char, 64> IP; // Permutation Table
    static array<char, 64> PI; // Inverse Permutation Table
    static array<char, 48> E; // Expansion table
    static array<char, 32> P; // Post S-Box permutation
    static array<array<char, 64>, 8> S; // Ths S-Box tables
    static array<char, 56> PC1; // Permuted Choice 1 Table
    static array<char, 48> PC2; // Permuted Choice 2 Table
    static array<char, 16> iteration_shift; // Iteration Shift Array
};

#endif
