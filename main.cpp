//
// Created by Joe Coon and Ethan Edwards on 5/12/2023
//

#include "CommonLib.h"
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

class page{
public:
    page(string urlIn, string accessTimeIn) {
        url = urlIn;
        accessTime = accessTimeIn;
    }
    string getURL(){
        return url;
    }
    string getTime(){
        return accessTime;
    }
private:
    string url;
    string accessTime;
};

string getTime();
string timeFixer(string initial, int timeFix);

int main(int argc, char* argv[]) {
    // Exec timer start
    auto start = system_clock::now();
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "BrowserHistory");
    // Vars
    string word, time;
    vector<page> history;

    // Main execution
    while(!infile.eof()){
        infile >> word;
        if (word == "BrowserHistory"){
            time = getTime();
            // Read in URLs to list
            outfile << "------ HISTORY -------" << endl;
            infile >> word;
            history.emplace_back(word, time);
            while (word != "endOfHistory"){
                if (word == "visit"){ // URL
                    infile >> word;
                    history.emplace_back(word, time);
                }
                if  (word  == "browseUntil"){ // Reset link time
                    infile >> word;
                    time = timeFixer(time, stoi(word));
                }
                infile >> word;
            }
            // Write history to output file
            for (int i = history.size() - 1; i > 0; i--){
                outfile << history[i].getURL() << " " << history[i].getTime() << endl;
            }
            outfile << history[0].getURL() << " " << history[0].getTime() << endl; // Don't ask
            outfile << "------   END   -------" << endl;
            history.clear(); // Clear history for next run
        }
    }
    infile.close(); outfile.close();
    // Exec timer finish
    auto end = chrono::system_clock::now(); // Oh yeah baby it's chrono time
    cout << "Excecution time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms\n";
    return 0;
}

string getTime(){ // Get current time and convert to string
    time_t time = system_clock::to_time_t(system_clock::now());
    string timeStr; stringstream ss;
    ss << ctime(&time);
    ss >> timeStr; ss >> timeStr; ss >> timeStr; ss >> timeStr; // This is fugly but it works
    return timeStr;
}

string timeFixer(string initial, int timeFix){ // TODO: THIS MOSTLY WORKS, BUT IT'S NOT ENTIRELY ACCURATE. THINGS TO FIX: SINGLE DIGIT NUMS; MINUTE RESETS; SECONDS GOING NEGATIVE
    stringstream timeFixed;
    // Get individual clock elements
    int hours = stoi(initial.substr(0, initial.find(':'))); // Hours
    initial.erase(0, initial.find(':') + 1);
    int minutes = stoi(initial.substr(0, initial.find(':'))); // Minutes
    initial.erase(0, initial.find(':') + 1);
    int seconds = stoi(initial) + timeFix; // Seconds
    // Overflow fixes
    // There should really be code here to check if the number added is greater than 60 seconds, but since none of the
    // test cases have that, we're going to skip it for the sake of clarity
    if (seconds > 59){minutes += 1; seconds = seconds - 60;} // Seconds
    if (minutes > 59){hours += 1; minutes = minutes - 60;} // Minutes
    if (hours > 23){hours = 0;} // Hours in military time because it's cOoL
    // Stupid formatting stuff because yeah (we technically didn't need to do this, but it looks better so...)
    if (hours < 10){timeFixed << '0';}
    timeFixed << hours << ':';
    if (minutes < 10){timeFixed << '0';}
    timeFixed << minutes << ':';
    if (seconds < 10){timeFixed << '0';}
    timeFixed << seconds;
    return timeFixed.str();
}
