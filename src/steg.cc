/** @file
 *  
 *  Author: Amey Chavan (apchavan)
 *  File description:-
 *  This is the encrypter.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <getopt.h>
#include "MatImage.h"
#include "TextFile.h"
#include "Error.h"

using namespace std;
using namespace Steganography;

// Global variables
string PROGRAM = "steg";

// Helper functions
void print_help();

//=========================== main() ==========================================
int main(int argc, char** argv)
{
    // Declare necessary strings
    string image_filename;
    string text_filename, text;
    string key;
    string stego_filename = "out.png";

    // Command line options
    int option_index = 0;
    option long_options[] = {
        {"help",      no_argument,       0, 'h'},
        {"text-file", required_argument, 0, 'f'},
        {"password",  required_argument, 0, 'p'},
        {"out-file",  required_argument, 0, 'o'},
        {0,0,0,0}
    };

    // Parse every option
    while (true)
    {
        int c = getopt_long(argc, argv, ":hf:p:o:", long_options, &option_index);

        // If parsing is complete, break out of loop
        if (c == -1) break;

        switch (c)
        {
            case 'h':
                print_help();
                return 0;

            case 'f':
                text_filename = string(optarg);
                break;

            case 'p':
                key = string(optarg);
                break;

            case 'o':
                stego_filename = string(optarg);
                break;

            case ':': // Missing argument
                error("Missing option argument");

            case '?': // Unknown option
                error("Unknown option");

            default:  // Unknown error
                error("Unknown error");
        }   // 'switch (c)' closed.
    }   // 'while (true)' closed.

    // There should be exactly 1 non-option argument
    if ( (argc - optind) != 1 ) 
    {
        print_help();
        return 1;
    }

    // Open the image
    image_filename = string(argv[optind++]);
    MatImage I;
    try 
    {
        I = image_filename;
    } 
    catch (IOError e) 
    {
        error(e);
    }

    // Get the text
    if (text_filename.empty()) 
    {
        string line;
        cout << ":: Enter message: (Press <CTRL-D> when finished)" << endl;
        getline(cin, text);
        while (getline(cin, line))
            text += "\n" + line;
        cin.clear();
    } 
    else 
    {
        TextFile textfile = TextFile::open(text_filename);
        text = textfile.str();
    }

    // Get the password
    if (key.empty()) 
    {
        cout << ":: Set a password: ";
        getline(cin, key);
    }

    // Steg
    try 
    {
        I.steg(text, key).save(stego_filename);
        cout << ":: Stego-image saved as '" << stego_filename << "'" << endl;
    } 
    catch (const exception& e) 
    {
        error(e);
    }

    return 0;
}   // 'main(int argc, char** argv)' closed.

//========================= print_help() ======================================
void print_help()
{
    cout << endl <<
        "USAGE:\n"
        "  " << PROGRAM << " [OPTION...] IMAGE-FILE\n";

    cout << endl <<
        "OPTIONS:\n"
        "  -h, --help             display this help message\n"
        "  -f, --text-file=FILE   set the text file to encrypt\n"
        "  -p, --password=PASSWD  set the password\n"
        "  -o, --out-file=FILE    set the output stego-image filename\n"
        "\n"
        "  If a text file is not provided by options, the program will take\n"
        "  the text from STDIN.\n";
}   // 'print_help()' closed.


