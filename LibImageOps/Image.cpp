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

        for (auto iter = begin(); iter++; iter != end()) {

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

Image& Image::add(Image& i1, Image& i2) {

}

Image& Image::subtract(Image& i1, Image& i2) {

}

Image& Image::invert(Image& i) {

}

Image& Image::mask(Image& i1, Image& i2) {

}

Image& Image::threshold(Image& i, int t) {

}

// IO

void Image::save(string outFile) {

}

void Image::load(string inFile) {
    
}

