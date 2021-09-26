#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "format.h"

using namespace std;

// Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long int sec) { 
  
  chrono::seconds seconds{sec};

  chrono::hours hours =
      chrono::duration_cast<chrono::hours>(seconds);

  seconds -= chrono::duration_cast<chrono::seconds>(hours);

  chrono::minutes minutes =
      chrono::duration_cast<chrono::minutes>(seconds);

  seconds -= chrono::duration_cast<chrono::seconds>(minutes);

  stringstream ss;

  ss << setw(2) << setfill('0') << hours.count()     // HH
     << setw(1) << ":"                                    // :
     << setw(2) << setfill('0') << minutes.count()   // MM
     << setw(1) << ":"                                    // :
     << setw(2) << setfill('0') << seconds.count();  // SS

  return ss.str();
  
   }