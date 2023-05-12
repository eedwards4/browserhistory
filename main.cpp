//
// Created by Joe Coon and Ethan Edwards on 5/12/2023
//

#include <iostream>
#include "CommonLib.h"

int main(int argc, char* argv[]) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "BrowserHistory");
    string word;

    while(!infile.eof()){
        infile >> word;
        if (word == "BrowserHistory"){
            // Read in URL to list
            
            while (word != "endOfHistory"){
                if (word == "visit"){ // URL

                }
                if  (word  == "browseUntil"){ // Reset link time

                }
            }
        } else if (word == "visit"){

        } else if  (word  == "browseUntil"){

        } else if (word == "endOfHistory"){

        }
    }
}

