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
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

using std::string;

namespace WHTMIC023 {

    class Filter {
        private:
            std::vector<float> filterVals;
            int width;

        public:
            Filter(std::string filename) {
                std::ifstream ifs = std::ifstream(filename);
                float val;

                ifs >> width;
                int size = width*width;

                filterVals = std::vector<float>();
                filterVals.reserve(size);
                for (int i = 0; i < size; i++) {
                    ifs >> val;
                    filterVals.push_back(val);
                }
                
                ifs.close();
            }

            float getValue(int i) {
                return filterVals[i];
            }

            int getFilterWidth() {
                return width;
            }
    };


    class Image {
        private:
            int width, height;
            std::unique_ptr <unsigned char[]> data;

        public:
            Image(); // default constructor

            Image(string inFile); // file constructor

            Image(std::istringstream& input); // Input stream constructor

            ~Image(); // destructor

            Image(Image& rhs); // copy constructor

            Image(Image&& rhs); // move constructor

            Image& operator=(Image& rhs); // copy assignment operator

            Image& operator=(Image&& rhs); // move assignment operator

            // IMAGE OPERATIONS

            static Image add( Image& i1,  Image& i2);

            static Image subtract( Image& i1,  Image& i2);

            static Image invert( Image& i);

            static Image mask( Image& i1,  Image& i2);

            static Image threshold( Image& i, int f);

            static Image filter( Image& i, Filter g);

            // IO

            void save(string outFile);

            void load(string inFile);

            // OPERATOR OVERLOADS

            Image operator+( Image& rhs) { // add
                return add(*this, rhs);
            }

            Image operator-( Image& rhs) { // subtract
                return subtract(*this, rhs);
            }

            Image operator!() { // invert
                return invert(*this);
            }

            Image operator/( Image& rhs) { // mask
                return mask(*this, rhs);
            }

            Image operator*( int rhs) { // threshold
                return threshold(*this, rhs);
            }

            Image operator%( Filter rhs) { // filter
                return filter(*this, rhs);
            }

	        friend std::ostream& operator<<(std::ostream& output, Image rhs);

	        friend std::istream& operator>>(std::istream& input, Image& rhs);

        // nested iterator class for working with images
        class iterator {
            friend Image;

            private:
                unsigned char *ptr;

                // construct only via Image class (begin/end)
                iterator(u_char *p) : ptr(p) {}

            public:
                iterator( const iterator & rhs) : ptr(rhs.ptr) {} // copy constructor
                
                // OPERATOR OVERLOADS
                iterator & operator=(const iterator & rhs) {
                    if (this != &rhs)
                        ptr = rhs.ptr;
                    return *this;
                }

                u_char & operator*() {
                    return *ptr;
                }

                iterator& operator++() { // prefix ++
                    ptr++;
                    return *this;
                }

                iterator& operator++(int rhs) { // postfix ++
                    return ++(*this);
                }       

                iterator& operator--() {  // prefix --
                    ptr--;
                    return *this;
                }

                iterator& operator--(int rhs) {  // postfix --
                    return --(*this);
                }

                bool operator!=(const iterator & rhs) { // !=
                    if (ptr == rhs.ptr)
                        return false;

                    else return true;
                }

                bool operator==(const iterator & rhs) { // ==
                    return !(*this != rhs);
                }
        };
        
        iterator begin(void) { return iterator(data.get()); }

        iterator end(void) { return iterator(data.get() + (width * height)); }
    };

    // IO Stream operators for image

    std::ostream& operator<<(std::ostream& output, Image rhs);

    std::istream& operator>>(std::istream& input, Image& rhs);

}

#endif