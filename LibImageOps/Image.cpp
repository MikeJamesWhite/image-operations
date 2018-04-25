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
    //cout << "Creating image" << endl;
    load(inFile);
}

Image::Image(std::istringstream & input) { // input stream constructor
    int i;
    input >> i >> std::ws;
    width = i;
    height = 1;
    data = std::unique_ptr<unsigned char []> ( new unsigned char [i] );

    int count = 0;
    while (!input.eof()) {
        input >> i >> std::ws;
        data[count] = (unsigned char) i;
        count++;
    }
}

Image::~Image() { // destructor
    //cout << "Destroying image" << endl;
    data = nullptr;
}

Image::Image(Image& rhs) { // copy constructor
    //cout << "Copying image" << endl;
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
    //cout << "Moving image" << endl;
    data = nullptr;

    std::swap(width, rhs.width);
    std::swap(height, rhs.height);
    std::swap(data, rhs.data);
}

Image& Image::operator=(Image& rhs) { // copy assignment operator
    //cout << "Copying image" << endl;
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
    //cout << "Moving image" << endl;
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

    if (i1.width != i2.width || i1.height != i2.height) { // throw error
        throw "Images are not the same dimensions as required...";
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

    if (i1.width != i2.width || i1.height != i2.height) { // throw error
        throw "Images are not the same dimensions as required...";
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

    if (i1.width != i2.width || i1.height != i2.height) { // throw error
        throw "Images are not the same dimensions as required...";
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

Image Image::filter(Image& img, Filter g) {
    cout << "Filtering image!" << endl;

    // set up returnImg
    Image returnImg;
    returnImg.width = img.width;
    returnImg.height = img.height;
    returnImg.data = std::unique_ptr<unsigned char []> ( new unsigned char [returnImg.width * returnImg.height] );

    // filter the return image
    for (int row = 0; row < returnImg.height; row++) {
        for (int col = 0; col < returnImg.width; col++) {
            
            int count = 0;
            int halfFilterWidth = g.getFilterWidth() / 2;
            float sum = 0.0f;
            for (int i = -halfFilterWidth; i < halfFilterWidth + 1; i++) {
                int y;
                if (row + i < 0  || row + i > returnImg.height) { // reflect y
                    y = row - i;
                }
                else {
                    y = row + i;
                }

                for (int j = -halfFilterWidth; j < halfFilterWidth + 1; j++) {
                    int x;
                    if (col + j < 0  || col + halfFilterWidth > returnImg.width) { // reflect x
                        x = col - j;
                    }
                    else {
                        x = col + j;
                    }

                    sum += ( (float) (*(img.data.get() + (y * img.width) + x)) ) * g.getValue(count);

                    count++;
                }
            }

            if (sum > 255)
                sum = 255;
            if (sum < 0)
                sum = 0;
            *(returnImg.data.get() + (row * returnImg.width) + col) = sum;
        }
    }

    return returnImg;
}

// File IO

void Image::save(string outFile) {
    cout << "Saving image to " << outFile << endl;
    cout << "Width: " << width << ", Height: " << height << endl;

    std::ofstream output = std::ofstream(outFile, std::ios_base::binary);
    output << *this;

    output.close();
}

void Image::load(string inFile) {
    cout << "Loading image from " << inFile << endl;

    std::ifstream input = std::ifstream(inFile,std::ios_base::binary);
    input >> *this;

    input.close();
}

// IO Stream Operators

std::ostream& WHTMIC023::operator<<(std::ostream& output, Image rhs) {
    // write header
    output << "P5" << std::endl;
    output << std::to_string(rhs.width) << " " << std::to_string(rhs.height) << std::endl;
    output << "255" << std::endl;

    // write binary data
    std::cout << "writing " << std::to_string(rhs.width*rhs.height) << " bytes" << std::endl << std::endl;
    output.write(reinterpret_cast<const char*> (rhs.data.get()), rhs.width*rhs.height);

    return output;
}

void WHTMIC023::operator>>(std::istream& input, Image& rhs) {
    string s = "";
    rhs.data = nullptr;

    // discard header lines
    std::getline(input, s);
    std::getline(input, s);
    while (s[0] == '#') {
        std::getline(input, s);
    }

    // parse height and width
    std::istringstream iss = std::istringstream( s );
    iss >> rhs.width;
    iss >> rhs.height;
    rhs.data = std::unique_ptr<unsigned char []> ( new unsigned char [rhs.width * rhs.height] );
    std::cout << "Width: " << rhs.width << ", Height: " << rhs.height << std::endl;

    std::getline(input, s);

    // read binary data
    std::cout << "reading " << std::to_string(rhs.width*rhs.height) << " bytes" << std::endl << std::endl;
    input.read(reinterpret_cast<char*> (rhs.data.get()), rhs.width * rhs.height);
}