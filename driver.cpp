/**
 * driver.cpp
 * 
 * Driver program to run the Image Operations program
 * 
 * Author: Michael White
 * Date: 16/04/2018
 */

#include "Image.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::istringstream;

using namespace WHTMIC023;

int main(int argc, char * argv []) {
    system("clear");
    cout << "Image Operations - by Michael White (WHTMIC023)" << endl;
    cout << "-----------------------------------------------" << endl << endl;
    
    string option = string(argv[1]);
    Image outputImg;

    if (option == "-a") { // option -a: add images
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i1(string(argv[2]));
        Image i2(string(argv[3]));

        outputImg = Image::add(i1, i2);
    }

    else if (option == "-s") { // option -s: subtract images
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i1(string(argv[2]));
        Image i2(string(argv[3]));

        outputImg = Image::subtract(i1, i2);
    }

    else if (option == "-i") { // option -i: invert image
        if (argc != 4) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i(string(argv[2]));

        outputImg = Image::invert(i);
    }

    else if (option == "-l") { // option -l: mask image
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i1(string(argv[2]));
        Image i2(string(argv[3]));

        outputImg = Image::mask(i1, i2);
    }

    else if (option == "-t") { // option -t: threshold image
        if (argc != 4) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i(string(argv[2]));
        int t;

        istringstream ss (string(argv[3]));
        ss >> t;

        outputImg = Image::threshold(i, t);
    }

    else {
        cout << "Unrecognised commandline option!" << endl;
        return 1;
    }

    cout << "Operation complete!" << endl;

    outputImg.save(argv[argc-1]);
    cout << "Outputted to file!" << endl;

    return 0;
}