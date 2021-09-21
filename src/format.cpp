#include <string>

#include "format.h"

using std::string;

// Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int seconds) { 
    int hours = seconds/3600;
    int minutes = (seconds%3600)/60;
    seconds = seconds%60;
    return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds); 
    }