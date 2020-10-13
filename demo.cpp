#include <iostream>
#include <array>
#include "crypto.h"
#include <opencv2/opencv.hpp>

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

void AES_CBCMode(){
    array<unsigned char, 16> key = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x1f, 0x2f, 0x3f, 0x4f, 0x5f, 0x6f, 0x7f, 0x8f};
    string imgPath = "./a.jpg";

    cv::Mat img;
    img = cv::imread(imgPath);

    if (!img.data) {
        printf("No image data read\n");
        exit(-1);
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("CBC MODE: original image", img);
    cv::waitKey();

    std::vector<unsigned char> img_data;
    int img_height = img.cols;
    int img_width = img.rows;

    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            img_data.push_back(pixel[0]);
            img_data.push_back(pixel[1]);
            img_data.push_back(pixel[2]);
        }
    }

    crypto::AES_CBC aes(key);
    auto ciphertext = aes.encrypt(img_data);

    cv::Mat_<cv::Vec3b> cipherImg = img;
    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            auto blue = ciphertext.at(y * img_width + x +0);
            auto green = ciphertext.at(y * img_width + x + 1);
            auto red = ciphertext.at(y*img_width + x +2);
            cipherImg(y, x)[0] = blue;
            cipherImg(y, x)[1] = green;
            cipherImg(y, x)[2] = red;
        }
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("CBC MODE: cipher image", cipherImg);
    cv::waitKey();

    auto plaintext = aes.decrypt(ciphertext);
    cv::Mat_<cv::Vec3b> plainImg = img;
    for (int y = img_height-1; y >= 0; y--) {
        for (int x = img_width-1; x >= 0; x--) {
            auto red = plaintext.back();
            plaintext.pop_back();
            auto green = plaintext.back();
            plaintext.pop_back();
            auto blue = plaintext.back();
            plaintext.pop_back();

            plainImg(y, x)[0] = blue;
            plainImg(y, x)[1] = green;
            plainImg(y, x)[2] = red;
        }
    }


    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("CBC MODE: plain image", plainImg);
    cv::waitKey();

}

void AES_ECBMode(){
    array<unsigned char, 16> key = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x1f, 0x2f, 0x3f, 0x4f, 0x5f, 0x6f, 0x7f, 0x8f};
    string imgPath = "./a.jpg";

    cv::Mat img;
    img = cv::imread(imgPath);

    if (!img.data) {
        printf("No image data read\n");
        exit(-1);
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("ECB MODE: original image", img);
    cv::waitKey();

    std::vector<unsigned char> img_data;
    int img_height = img.cols;
    int img_width = img.rows;

    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            img_data.push_back(pixel[0]);
            img_data.push_back(pixel[1]);
            img_data.push_back(pixel[2]);
        }
    }

    crypto::AES_ECB aes(key);
    auto ciphertext = aes.encrypt(img_data);

    cv::Mat_<cv::Vec3b> cipherImg = img;
    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            auto blue = ciphertext.at(y * img_width + x +0);
            auto green = ciphertext.at(y * img_width + x + 1);
            auto red = ciphertext.at(y*img_width + x +2);
            cipherImg(y, x)[0] = blue;
            cipherImg(y, x)[1] = green;
            cipherImg(y, x)[2] = red;
        }
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("ECB MODE: cipher image", cipherImg);
    cv::waitKey();

    auto plaintext = aes.decrypt(ciphertext);
    cv::Mat_<cv::Vec3b> plainImg = img;
    for (int y = img_height-1; y >= 0; y--) {
        for (int x = img_width-1; x >= 0; x--) {
            auto red = plaintext.back();
            plaintext.pop_back();
            auto green = plaintext.back();
            plaintext.pop_back();
            auto blue = plaintext.back();
            plaintext.pop_back();

            plainImg(y, x)[0] = blue;
            plainImg(y, x)[1] = green;
            plainImg(y, x)[2] = red;
        }
    }


    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("ECB MODE: plain image", plainImg);
    cv::waitKey();

}


int main(){
 //   demoAES();
//demoDES();
    //AES_CBCMode();
    AES_ECBMode();
    return 0;
}
