/**
 * Image.cpp
 * 
 * Implementation file for the Image Operations Library.
 * 
 * Author: Michael White
 * Date: 16/04/2018
 */

#include "Image.h"
#include <fstream>

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
    cout << "Creating image" << endl;
    load(inFile);
}

Image::~Image() { // destructor
    cout << "Destroying image" << endl;
    data = nullptr;
}

Image::Image(Image& rhs) { // copy constructor
    cout << "Copying image" << endl;
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
    cout << "Moving image" << endl;
    data = nullptr;

    std::swap(width, rhs.width);
    std::swap(height, rhs.height);
    std::swap(data, rhs.data);
}

Image& Image::operator=(Image& rhs) { // copy assignment operator
    cout << "Copying image" << endl;
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
    cout << "Moving image" << endl;
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
        cout << "Images are not the same dimensions as required..." << endl;
        std::exit(1);
    }
    
    Image returnImg = i1;
    auto iter1 = returnImg.begin();
    
    for (auto iter2 = i2.begin(); iter2 != i2.end(); iter2++) {
        int i = *iter2 + *iter1;
        if (i > 255)
            *iter1 = (u_char) 255;
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
        cout << "Images are not the same dimensions as required..." << endl;
        std::exit(1);
    }
    
    Image returnImg = i1;
    auto iter1 = returnImg.begin();
    
    for (auto iter2 = i2.begin(); iter2 != i2.end(); iter2++) {
        int i = *iter1 - *iter2;
        if (i < 0)
            *iter1 = (u_char) 0;
        else
            *iter1 -= *iter2;
        iter1++;
    }
    
    cout << "Ending subtract!" << endl;
    return returnImg;
}

Image Image::invert(Image& i) {
    cout << "Inverting image!" << endl;
    
    Image returnImg = i;
    
    for (auto iter = returnImg.begin(); iter != returnImg.end(); iter++) {
        *iter = (255 - *iter);
    }

    return returnImg;
}

Image Image::mask(Image& i1, Image& i2) {
    cout << "Masking image!" << endl;

    if (i1.width != i2.width || i1.height != i2.height) {
        //throw error
        cout << "Images are not the same dimensions as required..." << endl;
        std::exit(1);
    }
    
    Image returnImg = i1;
    auto iter1 = returnImg.begin();
    
    for (auto iter2 = i2.begin(); iter2 != i2.end(); iter2++) {
        if(*iter2 != 255)
            *iter1 = 0;

        iter1++;
    }

    return returnImg;
}

Image Image::threshold(Image& i, int f) {
    cout << "Thresholding image!" << endl;

    Image returnImg = i;
    
    for (auto iter = returnImg.begin(); iter != returnImg.end(); iter++) {
        if(*iter > f)
            *iter = 255;
        else
            *iter = 0;
    }

    return returnImg;
}

// File IO

void Image::save(string outFile) {
    cout << "Saving image to " << outFile << endl;
    cout << "Width: " << width << ", Height: " << height << endl;

    std::ofstream output = std::ofstream(outFile, std::ios_base::binary);

    // write header
    output << "P5" << endl;
    output << std::to_string(width) << " " << std::to_string(height) << endl;
    output << "255" << endl;

    // write binary data
    cout << "writing " << std::to_string(width*height) << " bytes" << endl << endl;
    output.write(reinterpret_cast<const char*> (data.get()), width*height);

    output.close();
}

void Image::load(string inFile) {
    cout << "Loading image from " << inFile << endl;

    std::ifstream input = std::ifstream(inFile,std::ios_base::binary);
    string s = "";
    data = nullptr;

    // discard header lines
    std::getline(input, s);
    std::getline(input, s);
    while (s[0] == '#') {
        std::getline(input, s);
    }

    // parse height and width
    std::istringstream iss = std::istringstream( s );
    iss >> width;
    iss >> height;
    data = std::unique_ptr<unsigned char []> ( new unsigned char [width * height] );
    cout << "Width: " << width << ", Height: " << height << endl;

    std::getline(input, s);

    // read binary data
    cout << "reading " << std::to_string(width*height) << " bytes" << endl << endl;
    input.read(reinterpret_cast<char*> (data.get()), width * height);

    input.close();
}