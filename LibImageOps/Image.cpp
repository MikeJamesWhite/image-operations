/**
 * Image.cpp
 * 
 * Implementation file for the Image Operations Library.
 * 
 * Author: Michael White
 * Date: 16/04/2018
 */

#include "Image.h"

using namespace WHTMIC023;
using std::endl;
using std::cout;

// special member functions
Image::Image() { // default constructor
    width = 0;
    height = 0;
    data = nullptr;
}

Image::Image(string inFile) { // file constructor
    load(inFile);
}

Image::~Image() { // destructor
    data = nullptr;
}

Image::Image(Image& rhs) { // copy constructor
    data = nullptr;

    width = rhs.width;
    height = rhs.height;
    data = std::unique_ptr<unsigned char []> ( new unsigned char [width * height] );

    // iterate over rhs and deep copy values to lhs
    auto rhsIter = rhs.begin();
    for (auto iter = begin(); iter != end(); iter++) {
        *iter = *rhsIter;
        rhsIter++;
    }
}

Image::Image(Image&& rhs) { // move constructor
    data = nullptr;

    std::swap(width, rhs.width);
    std::swap(height, rhs.height);
    std::swap(data, rhs.data);
}

Image& Image::operator=(Image& rhs) { // copy assignment operator
    if (this != &rhs) {
        data = nullptr;

        width = rhs.width;
        height = rhs.height;
        data = std::unique_ptr<unsigned char []> ( new unsigned char [width * height] );
        
        // iterate over rhs and deep copy values to lhs
        auto rhsIter = rhs.begin();
        for (auto iter = begin(); iter != end(); iter++) {
            *iter = *rhsIter;
            rhsIter++;
        }
    }
    return *this;
}

Image& Image::operator=(Image&& rhs) { // move assignment operator
    if (this != &rhs) {
        data = nullptr;

        std::swap(width, rhs.width);
        std::swap(height, rhs.height);
        std::swap(data, rhs.data);
    }
    return *this;
}

// static image operations

Image Image::add(Image& i1, Image& i2) {
    cout << "Adding images!" << endl;

    if (i1.width != i2.width || i1.height != i2.height) {
        //throw error
    }
    
    Image returnImg = i1;
    auto iter1 = returnImg.begin();
    
    for (auto iter2 = i2.begin(); iter2 != i2.end(); iter2++) {
        if(*iter2 + *iter1 > 255)
            *iter1 = 255;
        else
            *iter1 += *iter2;
        iter1++;
    }
    return returnImg;
}

Image Image::subtract(Image& i1, Image& i2) {
    cout << "Subtracting images!" << endl;

    if (i1.width != i2.width || i1.height != i2.height) {
        //throw error
    }
    
    Image returnImg = i1;
    auto iter1 = returnImg.begin();
    
    for (auto iter2 = i2.begin(); iter2 != i2.end(); iter2++) {
        if(*iter1 - *iter2 < 0)
            *iter1 = 0;
        else
            *iter1 -= *iter2;
        iter1++;
    }
    
    return returnImg;
}

Image Image::invert(Image& i) {
    cout << "Inverting image!" << endl;
    
    Image returnImg = i;
    
    for (auto iter = i.begin(); iter != i.end(); iter++) {
        *iter = 255 - *iter;
    }

    return returnImg;
}

Image Image::mask(Image& i1, Image& i2) {
    cout << "Masking image!" << endl;
    Image returnImg;

    if (i1.width != i2.width || i1.height != i2.height) {
        //throw error
    }
    
    Image returnImg = i1;
    auto iter1 = returnImg.begin();
    
    for (auto iter2 = i2.begin(); iter2 != i2.end(); iter2++) {
        if(*iter2 == 255)
            *iter1 = 0;
            
        iter1++;
    }

    return returnImg;
}

Image Image::threshold(Image& i, int t) {
    cout << "Thresholding image!" << endl;

    Image returnImg = i;
    
    for (auto iter = i.begin(); iter != i.end(); iter++) {
        if(*iter > t)
            *iter = 255;
        else
            *iter += 0;
    }

    return returnImg;
}

// IO

void Image::save(string outFile) {

}

void Image::load(string inFile) {

}