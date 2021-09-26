#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};
// constants
const std::string nMemTotal{"MemTotal:"};
const std::string nMemFree{"MemFree:"};
const std::string nMemAvail{"MemAvailable:"};
const std::string nBuffer{"Buffers:"};
const std::string nProc{"processes"};
const std::string nProcRun{"procs_running"};
// I using VmRSS instead of VmSize bc of https://man7.org/linux/man-pages/man5/proc.5.html
const std::string nVmSize{"VmRSS:"};
const std::string nUid{"Uid:"};
const std::string nPrName{"PRETTY_NAME"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
/*long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();*/

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif