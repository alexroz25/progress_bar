#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

constexpr int PROGRESS_BAR_WIDTH = 100;

void updateProgressBar(double pctDone, int progressBarWidth);

int main() {
    double pctDone = 0;
    while (pctDone < 1) {
        time_t t = time(0);   // get time now
        int now = t % 86400;
        
        tm printTime;
        localtime_s(&printTime, &t);
        cout << setw(2) << setfill('0') << (printTime.tm_hour % 12 == 0 ? 12 : printTime.tm_hour % 12) << ':'
            << setw(2) << setfill('0') << (printTime.tm_min) << ':'
            << setw(2) << setfill('0') << printTime.tm_sec
            << (printTime.tm_hour < 12 ? " AM" : " PM")
            << "\n";

        int start = 46800;
        int end = 76800;
        int totalTime = end - start;

        pctDone = static_cast<double>(now - start) / totalTime;

        updateProgressBar(pctDone, PROGRESS_BAR_WIDTH);

        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "\33[2K\r" << "\033[A" << "\33[2K\r";
    }
}

void updateProgressBar(double pctDone, int progressBarWidth) {
    // width does not include percent numbers or brackets on each end
    int numChars = pctDone * progressBarWidth;
    cout << '[';
    int i;
    for (i = 0; i < numChars-1; ++i) cout << '=';
    for (; i < numChars; ++i) cout << '>';
    while (i++ < progressBarWidth) cout << ' ';
    
    cout << "] " << pctDone*100 << "%";
}