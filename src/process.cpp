#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

Process::Process(int pid) : pid_(pid){

}

// Return this process's ID
int Process::Pid() { return pid_; }

///may be hear I need to use another formula... ??
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    long int uptime = UpTime();
    long int sysUptime = LinuxParser::UpTime();
    return (uptime/(float)sysUptime); 
    }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process a) { 
    return (a.CpuUtilization() > this->CpuUtilization());
     }                  