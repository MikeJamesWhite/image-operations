/**
 * Unit tests for the imageops library
 * 
 * Author: Michael White (WHTMIC023)
 * Date: 19/04/2018
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "LibImageOps/Image.h"

using namespace WHTMIC023;
using namespace std;

// File IO

TEST_CASE("File IO") {
    Image i;
    i << "test_files/testimage.pgm";
    i >> "test_files/testoutput.pgm";

    Image i2;
    i2 << "test_files/testoutput.pgm";

    bool same = true;
    auto iter2 = i2.begin();
    for (auto iter = i.begin(); iter != i.end(); iter++) {
        if (*iter != *iter2) {
            same = false;
            break;
        }
        iter2++;
    }

    if (iter2 != i2.end()) {
        same = false;
    }

    REQUIRE(same);
}


// Iterator methods & operators

TEST_CASE("Iterator") {
    istringstream s1 ("5 12 14 13 15 16");
    Image i(s1);
    auto iter = i.begin();

    SECTION("Dereference") {
        REQUIRE(*iter == 12);
    }

    SECTION("Increment") {
        iter++;
        REQUIRE(*iter == 14);
        iter++;
        REQUIRE(*iter == 13);
    }

    SECTION("Decrement") {
        iter++;
        iter++;
        iter--;
        REQUIRE(*iter == 14);
    }

    SECTION("Copying Iterator") {
        auto iter2 = iter;
        bool same = true;
        while (iter != i.end()) {
            if (*iter != *iter2)
                same = false;
            iter++;
            iter2++;
        }
        REQUIRE(same);
    }

    SECTION("Equality") {
        
    }
}

// Move & Copy Semantics

TEST_CASE("Copying") {
    istringstream s ("5 12 14 13 15 16");
    Image i(s);
    Image j (i);

    auto iter = j.begin();
    REQUIRE(*iter == 12);
    iter++;
    REQUIRE(*iter == 14);
    iter++;
    REQUIRE(*iter == 13);
    iter++;
    REQUIRE(*iter == 15);
    iter++;
    REQUIRE(*iter == 16);
}

TEST_CASE("Moving") {
    istringstream s ("5 12 14 13 15 16");
    Image i(s);
    Image j = move(i);

    auto iter = j.begin();
    REQUIRE(*iter == 12);
    iter++;
    REQUIRE(*iter == 14);
    iter++;
    REQUIRE(*iter == 13);
    iter++;
    REQUIRE(*iter == 15);
    iter++;
    REQUIRE(*iter == 16);
}

// Image operations

TEST_CASE("Image Operations") {
    istringstream s1 ("5 12 14 13 15 16");
    Image i(s1);

    SECTION("Addition") {
        istringstream s2 ("5 12 14 13 15 255");
        Image j(s2);
        Image k = Image::add(i,j);
        auto iter = k.begin();
        REQUIRE(*iter == 24);
        iter++;
        REQUIRE(*iter == 28);
        iter++;
        REQUIRE(*iter == 26);
        iter++;
        REQUIRE(*iter == 30);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Subtraction") {
        istringstream s2 ("5 10 12 10 11 255");
        Image j(s2);
        Image k = Image::subtract(i,j);
        auto iter = k.begin();
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(*iter == 4);
        iter++;
        REQUIRE(*iter == 0);
    }
    SECTION("Masking") {
        istringstream s2 ("5 0 0 255 0 255");
        Image j(s2);
        Image k = Image::mask(i,j);
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 13);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 16);
    }
    SECTION("Thresholding") {
        int t = 12;
        Image k = Image::threshold(i, t);
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Inverting") {
        Image k = Image::invert(i);
        auto iter = k.begin();
        REQUIRE(*iter == 255 - 12);
        iter++;
        REQUIRE(*iter == 255 - 14);
        iter++;
        REQUIRE(*iter == 255 - 13);
        iter++;
        REQUIRE(*iter == 255 - 15);
        iter++;
        REQUIRE(*iter == 255 - 16);
    }
    SECTION("Filtering") {
        // TO DO
    }
}

// Image operator overloads

TEST_CASE("Image Operator Overloads") {
    istringstream s1 ("5 12 14 13 15 16");
    Image i(s1);

    SECTION("Addition") {
        istringstream s2 ("5 12 14 13 15 255");
        Image j(s2);
        Image k = i+j;
        auto iter = k.begin();
        REQUIRE(*iter == 24);
        iter++;
        REQUIRE(*iter == 28);
        iter++;
        REQUIRE(*iter == 26);
        iter++;
        REQUIRE(*iter == 30);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Subtraction") {
        istringstream s2 ("5 10 12 10 11 255");
        Image j(s2);
        Image k = i-j;
        auto iter = k.begin();
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(*iter == 4);
        iter++;
        REQUIRE(*iter == 0);
    }
    SECTION("Masking") {
        istringstream s2 ("5 0 0 255 0 255");
        Image j(s2);
        Image k = i/j;
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 13);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 16);
    }
    SECTION("Thresholding") {
        int t = 12;
        Image k = i * t;
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Inverting") {
        Image k = !i;
        auto iter = k.begin();
        REQUIRE(*iter == 255 - 12);
        iter++;
        REQUIRE(*iter == 255 - 14);
        iter++;
        REQUIRE(*iter == 255 - 13);
        iter++;
        REQUIRE(*iter == 255 - 15);
        iter++;
        REQUIRE(*iter == 255 - 16);
    }
    SECTION("Filtering") {
        // TO DO
    }
}
