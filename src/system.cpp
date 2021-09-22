#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream> //for debug

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using namespace std;

    //I really cant understand how we can return a process or vector of processes
    //maybe I miss something?
// TODO: Return the system's CPU
Processor& System::Cpu() { 
    LinuxParser::CpuUtilization();
    
    return cpu_; 
    }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 

    return processes_; 
    }

// Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
    }

// Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
     }

// Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long int System::UpTime() { 
    long int uptime = LinuxParser::UpTime();
///    std::cout << "up " << uptime << std::endl;
    return uptime; 
    }