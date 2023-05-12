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
            outfile << history[0].getURL() << " " << history[0].getTime() << endl;
            //for (page i : history){
            //    outfile << i.getURL() << " " << i.getTime() << endl;
            //}
            outfile << "------   END   -------" << endl;
            history.clear(); // Clear history for next run
        }
    }
    infile.close(); outfile.close();
    // Exec timer finish
    auto end = chrono::system_clock::now();
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
    string timeFixed;
    // Get individual clock elements
    int time0 = stoi(initial.substr(0, initial.find(':')));
    initial.erase(0, initial.find(':') + 1);
    int time1 = stoi(initial.substr(0, initial.find(':')));
    initial.erase(0, initial.find(':') + 1);
    int time2 = stoi(initial) + timeFix;
    // Overflow fixes
    if (time2 >= 60){time1 += 1; time2 = 60 - time2;}
    if (time1 >= 60){time0 += 1; time1 = 00;}
    if (time0 >= 24){time0 = 00; time1 = 00; time2 = 00;}
    // Recompile
    timeFixed = to_string(time0) + ":" + to_string(time1) + ":" + to_string(time2);
    return timeFixed;
}
