//
// Created by Joe Coon and Ethan Edwards on 5/12/2023
//

#include <iostream>
#include "CommonLib.h"

int main(int argc, char* argv[]) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "BrowserHistory");

    while(!infile.eof()){

    }
}

