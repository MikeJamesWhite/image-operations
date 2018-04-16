#ifndef IMAGE_OPS
#define IMAGE_OPS
/**
 * Image.h
 * 
 * Header file for the Image Operations Library.
 * 
 * Author: Michael White
 * Date: 16/04/2018
 */

#include <iostream>
#include <string>
#include <memory>
#include <sstream>

using std::string;

namespace WHTMIC023 {

    class Image {
        private:
            int width, height;
            std::unique_ptr<unsigned char * []> data;

        public:
            // special member functions
            Image(string inFile);

            ~Image();

            // image operations

            static Image& add(Image& i1, Image& i2);

            static Image& subtract(Image& i1, Image& i2);

            static Image& invert(Image& i);

            static Image& mask(Image& i1, Image& i2);

            static Image& threshold(Image& i, int t);

            // output

            void save(string outFile);

            void load(string inFile);
    };


}

#endif