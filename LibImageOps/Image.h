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
            std::unique_ptr <unsigned char[]> data;

        public:
            Image(); // default constructor

            Image(string inFile); // file constructor

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

            static Image threshold( Image& i, int t);

            // IO

            void save(string outFile);

            void load(string inFile);

            // OPERATOR OVERLOADS

            Image&& operator+( Image& rhs) { // add
                return add(*this, rhs);
            }

            Image&& operator-( Image& rhs) { // subtract
                return subtract(*this, rhs);
            }

            Image&& operator!() { // invert
                return invert(*this);
            }

            Image&& operator/( Image& rhs) { // mask
                return mask(*this, rhs);
            }

            Image&& operator*( int rhs) { // threshold
                return threshold(*this, rhs);
            }

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
                    if (*ptr == *(rhs.ptr))
                        return false;

                    else return true;
                }

                bool operator==(const iterator & rhs) { // ==
                    return !(*this != rhs);
                }

                // other methods for iterator

        };
        
        iterator begin(void) { return iterator(data.get()); }

        iterator end(void) { return iterator(data.get() + (width * height)); }
    };


}

#endif