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
Image::Image(string inFile) {
    load(inFile);
}

Image::~Image() {

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

// output

void Image::save(string outFile) {

}

void Image::load(string inFile) {

}
