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

    if (option == "-a") { // option -a: add images
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i1( (string(argv[2])) );
        Image i2( (string(argv[3])) );

        Image outputImg = std::move(Image::add(i1, i2));

        cout << "Operation complete!" << endl << endl;

        outputImg.save(argv[argc-1]);
        cout << "Done!" << endl;
    }

    else if (option == "-s") { // option -s: subtract images
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i1( (string(argv[2])) );
        Image i2( (string(argv[3])) );

        Image outputImg = std::move(Image::subtract(i1, i2));

        cout << "Operation complete!" << endl << endl;

        outputImg.save(argv[argc-1]);
        cout << "Done!" << endl;
    }

    else if (option == "-i") { // option -i: invert image
        if (argc != 4) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i( (string(argv[2])) );

        Image outputImg = std::move(Image::invert(i));

        cout << "Operation complete!" << endl << endl;

        outputImg.save(argv[argc-1]);
        cout << "Done!" << endl;
    }

    else if (option == "-l") { // option -l: mask image
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i1( (string(argv[2])) );
        Image i2( (string(argv[3])) );

        Image outputImg = std::move(Image::mask(i1, i2));

        cout << "Operation complete!" << endl << endl;

        outputImg.save(argv[argc-1]);
        cout << "Done!" << endl;
    }

    else if (option == "-t") { // option -t: threshold image
        if (argc != 5) {
            cout << "Incorrect number of arguments for option " + option + "!" << endl;
            return 2;
        }
        Image i( (string(argv[2])) );
        int t;

        istringstream iss ( (string(argv[3])) );
        iss >> t;

        Image outputImg = std::move(Image::threshold(i, t));

        cout << "Operation complete!" << endl << endl;

        outputImg.save(argv[argc-1]);
        cout << "Done!" << endl;
    }

    else {
        cout << "Unrecognised commandline option!" << endl;
        return 1;
    }

    return 0;
}