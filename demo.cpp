#include <iostream>
#include <array>
#include "crypto.h"

using std::array;
using std::vector;

void demoDES(){
    // 64 bit key
    array<unsigned char, 8> key = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    // 64 bit plaintext
    array<unsigned char, 8> msg = {'1', '2', '3', '4', '5', '6', '7', '8'};
    crypto::DES des(key);
    // 64 bit ciphertext
    array<unsigned char, 8> ciphertext = des.encrypt(msg);
    auto plaintext = des.decrypt(ciphertext);
}

void demoAES(){
    // 128 bit key
    array<unsigned char, 16> key = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x1f, 0x2f, 0x3f, 0x4f, 0x5f, 0x6f, 0x7f, 0x8f};
    // 128 bit plaintext
    array<unsigned char, 16> msg = {'1', '2', '3', '4', '5', '6', '7', '8', '8', '7', '6', '5', '4', '3', '2', '1'};
    crypto::AES aes(key);
    // 128 bit ciphertext
    auto ciphertext = aes.encrypt(msg);
    auto plaintext = aes.decrypt(ciphertext);
}

void AES_ECBmode(){
    std::vector<unsigned char> key = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x1f, 0x2f, 0x3f, 0x4f, 0x5f, 0x6f, 0x7f, 0x8f};
    string imgPath = "";



    crypto::AES_CBC aes(key);
    auto ciphertext = aes.encrypt()
}

void AES_CBCmode(){

}


int main(){
    demoAES();
    demoDES();
    return 0;
}
